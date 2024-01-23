
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <MQTTAsync.h>
#include "QuestFitNetworkCommunication.h"

#include "QuestFitCommon.h"
#include "eLog.h"
#include "QuestFitNetworkTypes.h"
#include "QuestFitNetworkInterface.h"
#ifdef _MSC_VER
#include <windows.h>
int gettime_c(struct timespec *spec) //C-file part
{
    __int64 wintime;
    GetSystemTimeAsFileTime((FILETIME *)&wintime);
    wintime -= 116444736000000000i64;            //1jan1601 to 1jan1970
    spec->tv_sec = wintime / 10000000i64;        //seconds
    spec->tv_nsec = wintime % 10000000i64 * 100; //nano-seconds
    return 0;
}
#else
int gettime(struct timespec *spec) //C-file part
{
    clock_gettime(CLOCK_MONOTONIC, spec);
    return 0;
}
#endif
struct timespec diff_c(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

MQTTAsync client;
MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;

bool mqttConnected = false;
uint64_t numberOfSamples = 0;
struct timespec time1, time2;
// MQTT Message storage
static QuestFitpe_config_t net_pe_config;
static QuestFitpe_status_t net_pe_status;
static QuestFitfpe_enumeration_t net_fpe_enumeration;
static QuestFitfpe_status_response_t net_fpe_status;
static QuestFitfpe_config_response_t net_fpe_config;
static QuestFitdebug_sample_t net_debug_sample;

int QuestFitNetworkComm_msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{

    // Decode PE configuration response
    if (strncmp(topicName, "testbn123/", 3) == 0)
    {
        if (strncmp(topicName, "testbn123/getNumber", 19) == 0)
        {
            int res = atoi(message->payload);
            QuestFitNetworkInterface_setTestNumber(res);
        }
    }
    if (strncmp(topicName, "pe/", 3) == 0)
    {
        elogInfo("Got Message from topic %s", topicName);
        if (strncmp(topicName, "pe/config/response", 18) == 0)
        {
            if (QuestFitNetwork_Process_PE_Config_Message(message->payload, message->payloadlen, &net_pe_config) == QFE_OK)
            {
                QuestFitNetworkInterface_setPeConfig(&net_pe_config);
            }
        }
        if (strncmp(topicName, "pe/status/response", 18) == 0)
        {
            if (QuestFitNetwork_Process_PE_Status_Message(message->payload, message->payloadlen, &net_pe_status) == QFE_OK)
            {
                QuestFitNetworkInterface_setPeStatus(&net_pe_status);
            }
        }
        else if (strncmp(topicName, "pe/enumeration/response", 23) == 0)
        {
            if (QuestFitNetwork_Process_FPE_Enumeration_Message(message->payload, message->payloadlen, &net_fpe_enumeration) == QFE_OK)
            {
                QuestFitNetworkInterface_setFpeEnumeration(&net_fpe_enumeration);
            }
        }
    }

    else if (strncmp(topicName, "fpe/", 4) == 0)
    {
        // Tokenize topicname
        char *token_ctx = NULL;
        // Throw away "fpe"
        strtok_s(topicName, "/", &token_ctx);
        // Get the serial number
        char *fpeSerialNumber = strtok_s(NULL, "/", &token_ctx);
        // Get the rest of the topic name for comparison
        char *command = strtok_s(NULL, "", &token_ctx);

        if (strncmp(command, "status/response", 18) == 0)
        {
            elogInfo("Got Message from FPE - Serial: %s Command: %s", fpeSerialNumber, command);
            if (QuestFitNetwork_Process_FPE_Status_Message(message->payload, message->payloadlen, &net_fpe_status) == QFE_OK)
            {
                QuestFitNetworkInterface_setFpeStatus(&net_fpe_status, fpeSerialNumber);
            }
        }
        else if (strncmp(command, "config/response", 15) == 0)
        {
            elogInfo("Got Message from FPE - Serial: %s Command: %s", fpeSerialNumber, command);
            if (QuestFitNetwork_Process_FPE_Config_Message(message->payload, message->payloadlen, &net_fpe_config) == QFE_OK)
            {
                QuestFitNetworkInterface_setFpeConfig(&net_fpe_config, fpeSerialNumber);
            }
        }
        else if (strncmp(command, "calProgress/response", 15) == 0)
        {
            elogInfo("Got Message from FPE - Serial: %s Command: %s", fpeSerialNumber, command);
            int32_t progress;
            progress = *(int32_t *)message->payload;
            QuestFitNetworkInterface_setCalibrationProgress(progress, fpeSerialNumber);
        }
#ifdef SIM_ENABLED
        else if (strncmp(command, "debug_sim_data", 10) == 0)
#else
        else if (strncmp(command, "debug_data", 10) == 0)
#endif
        {
            if (QuestFitNetwork_Process_FPE_debug_Data_Message(message->payload, message->payloadlen, &net_debug_sample) == QFE_OK)
            {
                QuestFitNetworkInterface_storeDebugSample(&net_debug_sample, fpeSerialNumber);
            }
            if (++numberOfSamples == 1)
            {
                gettime_c(&time1);
            }
            // 10 minutes at 1700hz
            else if (numberOfSamples % 102000 == 0)
            {
                gettime_c(&time2);
                struct timespec elapsed = diff_c(time1, time2);
                elogInfo("Got %ld/%ld (reported) samples in %ld:%ld\n", numberOfSamples, net_debug_sample.PE_SequenceNumber - 1, elapsed.tv_sec, elapsed.tv_nsec);
            }
        }
    }

    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}
void connlost(void *context, char *cause)
{
    int rc;

    if (cause)
    {
        elogError("MQTT connection lost: cause: %s", cause);
    }
    else
    {
        elogError("MQTT connection lost");
    }

    if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
    {
        elogError("Failed to start connect, return code %d", rc);
    }
}

void onDisconnectFailure(void *context, MQTTAsync_failureData *response)
{
    elogError("Disconnect failed, rc %d", response->code);
    mqttConnected = false;
}

// -------------------------------------------------------------------------
void onDisconnect(void *context, MQTTAsync_successData *response)
{
    elogInfo("Successful disconnection");
    mqttConnected = false;
}

// -------------------------------------------------------------------------
void onSubscribe(void *context, MQTTAsync_successData *response)
{
    elogInfo("Subscribe succeeded");
}

// -------------------------------------------------------------------------
void onSubscribeFailure(void *context, MQTTAsync_failureData *response)
{
    elogError("Subscribe failed, rc %d", response->code);
}

// -------------------------------------------------------------------------
void onConnectFailure(void *context, MQTTAsync_failureData *response)
{
    elogError("Connect failed, rc %d", response->code);
}

void onConnect(void *context, MQTTAsync_successData *response)
{
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    elogInfo("Connected!!");
    mqttConnected = true;
    opts.onSuccess = onSubscribe;
    opts.onFailure = onSubscribeFailure;

    MQTTAsync_subscribe(client, "pe/+/response", 0, &opts);
    MQTTAsync_subscribe(client, "fpe/+/+/response", 0, &opts);
    MQTTAsync_subscribe(client, "fpe/+/debug_data", 0, &opts);
    MQTTAsync_subscribe(client, "fpe/+/debug_sim_data", 0, &opts);
    MQTTAsync_subscribe(client, "testbn123/#", 0, &opts);
}

int QuestFitNetworkComm_connect()
{
    int rc;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = onConnect;
    conn_opts.onFailure = onConnectFailure;
    conn_opts.context = client;

    disc_opts.onSuccess = onDisconnect;
    disc_opts.onFailure = onDisconnectFailure;
    char client_name[20] = "questfitsdk";
    srand(time(0));
    client_name[11] = 'A' + ((double)rand() / RAND_MAX) * ('z' - 'A' - 1);
    client_name[12] = 'A' + ((double)rand() / RAND_MAX) * ('z' - 'A' - 1);
    client_name[13] = 'A' + ((double)rand() / RAND_MAX) * ('z' - 'A' - 1);
    client_name[14] = 0;

    // if ((rc = MQTTAsync_create(&client, "tcp://test.mosquitto.org:1883", "questfitsdk",
    if ((rc = MQTTAsync_create(&client, "tcp://192.168.20.50:1883", client_name,
                               MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS)
    {
        printf("Failed to create client, return code %d", rc);
        return -1;
    }

    if ((rc = MQTTAsync_setCallbacks(client, NULL, connlost, QuestFitNetworkComm_msgarrvd, NULL)) != MQTTASYNC_SUCCESS)
    {
        printf("Failed to set callbacks, return code %d", rc);
        return -1;
    }

    if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
    {
        printf("Failed to connect, return code %d", rc);
        return -1;
    }
    return 0;
}
int QuestFitNetworkComm_Destroy()
{
    MQTTAsync_disconnect(client, NULL);
    return 0;
}
bool QuestFitNetworkComm_is_connected()
{

    return mqttConnected;
}
int QuestFitNetworkComm_publish_message(const char *topic, void *payload, size_t payloadlen)
{
    int rc;
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

    if (mqttConnected)
    {
        opts.context = client;
        pubmsg.payload = payload;
        pubmsg.payloadlen = payloadlen;
        pubmsg.qos = 1;
        pubmsg.retained = 0;
        if ((rc = MQTTAsync_sendMessage(client, topic, &pubmsg, &opts)) != MQTTASYNC_SUCCESS)
        {
            elogError("Failed to start sendMessage, ret=%d, topic=%s", rc, topic);
            return -1;
        }
    }
    else
    {
        return -2;
    }

    return 0;
}

int QuestFitNetworkComm_discover_pe()
{

    return 0;
}
