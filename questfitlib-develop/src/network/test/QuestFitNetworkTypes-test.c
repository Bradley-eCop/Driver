#include "QuestFitNetworkTypes.h"
#include "QuestFitNetworkCommunication.h"
#include "QuestFitNetworkInterface.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "eLog.h"
#ifdef _MSC_VER
#include <windows.h>
int gettime(struct timespec *spec) //C-file part
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
struct timespec diff(struct timespec start, struct timespec end)
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

#define TEST_THROUGHPUT_SIZE 1E6
char testBuf[] = {
    0x01, 0xd0, 0x07, 0x01, 0x01, 0x02, 0x31, 0x32, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x32, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x32, 0x32, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x32, 0x33, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

int main(void)
{
    int i = 0;

    printf("Result is %d\n", process_int(1));
    QuestFitfpe_enumeration_t testenum;
    printf("Size is %d\n", (int)sizeof(testenum.serial_number));

    QuestFitpe_config_t resp = {
        .mode = QUESTFIT_MODE_FREE_RUN,
        .sample_rate_hz = 2000,
        .sim_enabled = 1,
        .fpe_list = {
            {.enabled = 1, .operating_mode = 2, .serial_number = "120"},
            {.enabled = 0, .serial_number = "121"},
            {.enabled = 0, .serial_number = "122"},
            {.enabled = 0, .serial_number = "123"}}};
    uint8_t *buf = (uint8_t*) &resp;
    for (i = 0; i < sizeof(QuestFitpe_config_t); i++)
    {
        printf("0x%02x, ", buf[i]);
    }
    QuestFitpe_config_t config;
    QuestFitError_e err;
    struct timespec time1, time2;
    gettime(&time1);
    for (i = 0; i < TEST_THROUGHPUT_SIZE; i++)
    {
        err = QuestFitNetwork_Process_PE_Config_Message(testBuf, sizeof(testBuf), &config);
        if (err == QFE_OK)
        {
        }
    }
    gettime(&time2);
    struct timespec elapsed = diff(time1, time2);
    double rate = (((double)i) / (((double)elapsed.tv_sec) * 1E9 + (double)elapsed.tv_nsec)) * 1E3;
    printf("\n\nPerformed %d operations in %ld:%ld, rate %.2lf MHz\n", i, (long)elapsed.tv_sec, (long)elapsed.tv_nsec, rate);

    elogInfo("Test 123");

    QuestFitNetworkInterface_Initialize();
#ifdef _MSC_VER
    Sleep(5000);
#else
    sleep(20);
#endif
    elogInfo("Requesting PE config");
    QuestFitpe_config_t config2;
    if (QuestFitNetworkInterface_getPeConfig(&config2, true) != QFE_OK)
    {
        elogInfo("Did not get PE Config");
        return 0;
    }
    elogInfo("Got PE config");
    buf = (uint8_t *)&config2;
    for (i = 0; i < sizeof(QuestFitpe_config_t); i++)
    {
        printf("0x%02x, ", buf[i]);
    }

    elogInfo("Requesting FPE enumeration");
    QuestFitfpe_enumeration_t enumeration;
    if (QuestFitNetworkInterface_getFpeEnumeration(&enumeration, true) == QFE_OK)
    {
        elogInfo("Got PE enumeration");
        buf = (uint8_t *)&enumeration;
        for (i = 0; i < sizeof(QuestFitfpe_enumeration_t); i++)
        {
            printf("0x%02x, ", buf[i]);
        }
    }
    else
    {
        elogError("Error getting enumeration");
    }
    elogInfo("Getting status");
    QuestFitfpe_status_response_t fpeStatus;
    if (QuestFitNetworkInterface_getFpeStatus(&fpeStatus, "00015", true) == QFE_OK)
    {
        elogInfo("Got FPE status %d.%d.%d", fpeStatus.sw_version_major, fpeStatus.sw_version_minor, fpeStatus.sw_revision);
    }
    QuestFitfpe_config_response_t fpeConfig;
    if (QuestFitNetworkInterface_getFpeConfig(&fpeConfig, "00015", true) == QFE_OK)
    {
        elogInfo("Got FPE config model: %s serial: %s mode: 0x%x", fpeConfig.FPE_ModelNumber, fpeConfig.FPE_SerialNumber, fpeConfig.OperatingMode);
    }

    elogInfo("Starting Debug");
    char serialNumber[68] = {0};
    // Get current configuration
    QuestFitpe_config_t config3;
    QuestFitNetworkInterface_getFpeEnumeration(&enumeration, true);
    QuestFitNetworkInterface_getPeConfig(&config3, true);
    // Enable raw data mode on the first connected FPE
    strcpy(config3.fpe_list[0].serial_number, enumeration.serial_number[0]);
    strcpy(serialNumber, enumeration.serial_number[0]);
    config3.fpe_list[0].enabled = true;
    config3.fpe_list[0].operating_mode = QUESTFIT_FPE_MODE_DEBUG;
    config3.mode = QUESTFIT_MODE_FREE_RUN;
    config3.sample_rate_hz = 2000;
    config3.sim_enabled = false;
    elogInfo("SENDING PE config");
    buf = (uint8_t *)&config3;
    for (i = 0; i < sizeof(QuestFitpe_config_t); i++)
    {
        printf("0x%02x, ", buf[i]);
    }
    // QuestFitNetworkInterface_sendPlatformUpdate("C:\\Users\\William Neuson\\Downloads\\cba-1.0.1.swu");
    QuestFitNetworkInterface_sendPeConfig(&config3);
    // Enable raw data in the interface driver
    QuestFitNetworkInterface_startDebugMode(serialNumber);
    QuestFitNetworkInterface_getPeConfig(&config3, true);
    elogInfo("Got PE config");
    buf = (uint8_t *)&config3;
    for (i = 0; i < sizeof(QuestFitpe_config_t); i++)
    {
        printf("0x%02x, ", buf[i]);
    }
    // QuestFitNetworkInterface_sendPlatformUpdate("C:\\Users\\William Neuson\\Downloads\\cba-1.0.1.swu");
    int counter = 0;
    size_t data_retrieved = 0;
    QuestFitdebug_sample_t samples[8000];

    while (true)
    {
#ifdef _MSC_VER
        Sleep(1000);
#else
        sleep(1);
#endif
        elogInfo("Trying to get sample");
        QuestFitNetworkInterface_getDebugSamples(samples, serialNumber, 8000, &data_retrieved, false);
        if (data_retrieved >= 1)
        {
            elogInfo("Retrieved %d samples after %d seconds", data_retrieved, counter);
            break;
        }
        counter++;
    }
    Sleep(4000);
    QuestFitNetworkInterface_getDebugSamples(samples, serialNumber, 8000, &data_retrieved, false);
    QuestFitNetworkInterface_getDebugSamples(samples, serialNumber, 8000, &data_retrieved, false);
    QuestFitNetworkInterface_getDebugSamples(samples, serialNumber, 8000, &data_retrieved, false);
    counter = 0;
    FILE *fptr;
    fptr = fopen("data.csv", "w");
    if (fptr == NULL)
    {
        elogInfo("Couldn't open file");
    }
    fprintf(fptr, "Fx1, Fy1, Fz1, Fx2, Fy2, Fz2, Fx3, Fy3, Fz3, Fx4, Fy4, Fz4, Fx, Fy, Fz, Mx, My, Mz\n");
    size_t totalSamples = 0;

    gettime(&time1);
    while (counter < 20)
    {
#ifdef _MSC_VER
        Sleep(1000);
#else
        sleep(1);
#endif
        elogInfo("Trying to get sample");
        QuestFitNetworkInterface_getDebugSamples(samples, serialNumber, 8000, &data_retrieved, false);
        if (data_retrieved >= 1)
        {
            totalSamples += data_retrieved;
            elogInfo("Retrieved %d samples after %d seconds", data_retrieved, counter);
            for (int j = 0; j < data_retrieved; j++)
            {
                fprintf(fptr, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n",
                        samples[j].Fx12,
                        samples[j].Fx34,
                        samples[j].Fy14,
                        samples[j].Fy23,
                        samples[j].Fz1,
                        samples[j].Fz2,
                        samples[j].Fz3,
                        samples[j].Fz4,
                        samples[j].Fx,
                        samples[j].Fy,
                        samples[j].Fz,
                        samples[j].Mx,
                        samples[j].My,
                        samples[j].Mz);
            }
        }
        counter++;
    }
    fclose(fptr);
    gettime(&time2);
    elapsed = diff(time1, time2);
    rate = (((double)totalSamples) / (((double)elapsed.tv_sec) * 1E9 + (double)elapsed.tv_nsec)) * 1E6;
    printf("\n\nGot %d samples in %ld:%ld, rate %.2lf KHz\n", (int)totalSamples, elapsed.tv_sec, elapsed.tv_nsec, rate);

    // #ifdef _MSC_VER
    //     Sleep(10000);
    // #else
    //     sleep(20);
    // #endif
    elogInfo("Getting config");
    QuestFitNetworkInterface_getFpeEnumeration(&enumeration, true);
    QuestFitNetworkInterface_getPeConfig(&config3, true);
    // Enable raw data mode on the first connected FPE
    strcpy(config3.fpe_list[0].serial_number, enumeration.serial_number[0]);
    config3.fpe_list[0].enabled = false;
    config3.fpe_list[0].operating_mode = QUESTFIT_FPE_MODE_IDLE;
    config3.mode = QUESTFIT_MODE_IDLE;
    config3.sample_rate_hz = 2000;
    config3.sim_enabled = false;
    elogInfo("Sending config to stop debug");
    QuestFitNetworkInterface_sendPeConfig(&config3);
    elogInfo("Getting config");
    if (QuestFitNetworkInterface_getPeConfig(&config3, true) != QFE_OK)
    {
        elogInfo("Didn't get config");
    }
    // Enable raw data in the interface driver
    QuestFitNetworkInterface_stopDebugMode(serialNumber);

    return 0;
}