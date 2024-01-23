#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "QuestFitNetworkInterface.h"
#include "QuestFitNetworkCommunication.h"
#include "QuestFitCircularBuffer.h"
#define DEBUG_DATA_SAMPLE_COUNT 8000
#define MAX_FILE_SIZE 1024 * 1024 * 300 // 300MB

static QuestFitpe_config_t current_pe_config;
static QuestFitpe_status_t current_pe_status;
static QuestFitfpe_enumeration_t current_fpe_enumeration;
static QuestFitfpe_status_response_t current_fpe_status;
static QuestFitfpe_config_response_t current_fpe_config;
static qfcircular_buf_handle_t debug_circular_buffer = NULL;
static char currentDebugSerialNumber[64] = {0};
static int current_test_number = 0;
static int32_t current_cal_progress_number = 0;

#ifdef _MSC_VER
#define F_OK 4
#include <windows.h>
static LONG current_transaction_id = 0;
uint32_t get_transaction_id()
{
    return (uint32_t)InterlockedIncrement(&current_transaction_id);
}
#else
#include <unistd.h>
static uint32_t current_transaction_id = 0;
uint32_t get_transaction_id()
{
    return current_transaction_id++;
}
#endif

#ifdef _MSC_VER
HANDLE peConfigSemaphore;
HANDLE peStatusSemaphore;
HANDLE fpeEnumerationSemaphore;
HANDLE fpeStatusSemaphore;
HANDLE fpeConfigSemaphore;
HANDLE testNumSemaphore;
static QuestFitError_e post_sem(HANDLE sem)
{
    ReleaseSemaphore(
        sem,   // handle to semaphore
        1,     // increase count by one
        NULL); // not interested in previous count
    return QFE_OK;
}
static QuestFitError_e wait_for_sem(HANDLE sem)
{
    DWORD dwWaitResult = WaitForSingleObject(
        sem,    // handle to semaphore
        2000L); // zero-second time-out interval

    switch (dwWaitResult)
    {
    // The semaphore object was signaled.
    case WAIT_OBJECT_0:
        return QFE_OK;

        break;
    // The semaphore was nonsignaled, so a time-out occurred.
    case WAIT_TIMEOUT:
        return QFE_TIMEOUT;
        break;
    }
    return QFE_TIMEOUT;
}
#endif
QuestFitError_e QuestFitNetworkInterface_setPeConfig(QuestFitpe_config_t *config)
{
    memcpy(&current_pe_config, config, sizeof(QuestFitpe_config_t));
    post_sem(peConfigSemaphore);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_getPeConfig(QuestFitpe_config_t *config, bool blockForUpdate)
{
    if (blockForUpdate)
    {
        if (!QuestFitNetworkComm_is_connected())
        {
            return QFE_NOT_CONNECTED;
        }
        QuestFitpe_command_t command = {
            .transaction_id = get_transaction_id(),
            .command = QUESTFIT_PE_CMD_GET_CONFIG};
        QuestFitNetworkComm_publish_message("pe/command/request", &command, sizeof(command));
        if (wait_for_sem(peConfigSemaphore) == QFE_TIMEOUT)
        {
            return QFE_TIMEOUT;
        }
    }
    memcpy(config, &current_pe_config, sizeof(QuestFitpe_config_t));
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_sendPeConfig(QuestFitpe_config_t *config)
{
    if (!QuestFitNetworkComm_is_connected())
    {
        return QFE_NOT_CONNECTED;
    }
    QuestFitNetworkComm_publish_message("pe/config/request", config, sizeof(QuestFitpe_config_t));
    return QFE_OK;
}
/**
 * Initializes a PE config structure to a known blank state
 * 
 */
QuestFitError_e QuestFitNetworkInterface_initializePeConfig(QuestFitpe_config_t *config)
{
    int i = 0;
    config->mode = QUESTFIT_MODE_IDLE;
    config->sample_rate_hz = 2000;
    config->sim_enabled = false;
    for(i=0; i<QUESTFIT_NUM_INPUTS; i++)
    {
        config->fpe_list[i].enabled = 0;
        config->fpe_list[i].operating_mode = QUESTFIT_FPE_MODE_IDLE;
        memset(config->fpe_list[i].serial_number, 0, sizeof(config->fpe_list[i].serial_number));
    }
    return QFE_OK;

}

QuestFitError_e QuestFitNetworkInterface_setPeStatus(QuestFitpe_status_t *status)
{
    memcpy(&current_pe_status, status, sizeof(QuestFitpe_status_t));
    post_sem(peStatusSemaphore);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_getPeStatus(QuestFitpe_status_t *status, bool blockForUpdate)
{
    if (blockForUpdate)
    {
        if (!QuestFitNetworkComm_is_connected())
        {
            return QFE_NOT_CONNECTED;
        }
        QuestFitpe_command_t command = {
            .transaction_id = get_transaction_id(),
            .command = QUESTFIT_PE_CMD_GET_STATUS};
        QuestFitNetworkComm_publish_message("pe/command/request", &command, sizeof(command));
        if (wait_for_sem(peStatusSemaphore) == QFE_TIMEOUT)
        {
            return QFE_TIMEOUT;
        }
    }
    memcpy(status, &current_pe_status, sizeof(QuestFitpe_status_t));
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_setFpeEnumeration(QuestFitfpe_enumeration_t *enumeration)
{
    memcpy(&current_fpe_enumeration, enumeration, sizeof(QuestFitfpe_enumeration_t));
    post_sem(fpeEnumerationSemaphore);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_getFpeEnumeration(QuestFitfpe_enumeration_t *enumeration, bool blockForUpdate)
{
    if (blockForUpdate)
    {
        if (!QuestFitNetworkComm_is_connected())
        {
            return QFE_NOT_CONNECTED;
        }
        QuestFitpe_command_t command = {
            .transaction_id = get_transaction_id(),
            .command = QUESTFIT_PE_CMD_ENUMERATE_PLATES};
        QuestFitNetworkComm_publish_message("pe/command/request", &command, sizeof(command));
        if (wait_for_sem(fpeEnumerationSemaphore) == QFE_TIMEOUT)
        {
            return QFE_TIMEOUT;
        }
    }
    memcpy(enumeration, &current_fpe_enumeration, sizeof(QuestFitfpe_enumeration_t));
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_setFpeStatus(QuestFitfpe_status_response_t *status, char *serial)
{
    memcpy(&current_fpe_status, status, sizeof(QuestFitfpe_status_response_t));
    post_sem(fpeStatusSemaphore);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_getFpeStatus(QuestFitfpe_status_response_t *status, char *serialNumber, bool blockForUpdate)
{
    if (blockForUpdate)
    {
        if (!QuestFitNetworkComm_is_connected())
        {
            return QFE_NOT_CONNECTED;
        }
        QuestFitfpe_command_request_t command = {
            .transaction_id = get_transaction_id(),
            .command = QUESTFIT_FPE_CMD_GET_STATUS};
        char fpeCommandTopic[100] = "";
        sprintf_s(fpeCommandTopic, sizeof(fpeCommandTopic), "fpe/%s/command/request", serialNumber);
        QuestFitNetworkComm_publish_message(fpeCommandTopic, &command, sizeof(command));
        if (wait_for_sem(fpeStatusSemaphore) == QFE_TIMEOUT)
        {
            return QFE_TIMEOUT;
        }
    }
    memcpy(status, &current_fpe_status, sizeof(QuestFitfpe_status_response_t));
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_setFpeConfig(QuestFitfpe_config_response_t *config, char *serial)
{
    memcpy(&current_fpe_config, config, sizeof(QuestFitfpe_config_response_t));
    post_sem(fpeConfigSemaphore);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_getFpeConfig(QuestFitfpe_config_response_t *config, char *serialNumber, bool blockForUpdate)
{
    if (blockForUpdate)
    {
        if (!QuestFitNetworkComm_is_connected())
        {
            return QFE_NOT_CONNECTED;
        }
        QuestFitfpe_command_request_t command = {
            .transaction_id = get_transaction_id(),
            .command = QUESTFIT_FPE_CMD_GET_CONFIG};
        char fpeCommandTopic[100] = "";
        sprintf_s(fpeCommandTopic, sizeof(fpeCommandTopic), "fpe/%s/command/request", serialNumber);
        QuestFitNetworkComm_publish_message(fpeCommandTopic, &command, sizeof(command));
        if (wait_for_sem(fpeConfigSemaphore) == QFE_TIMEOUT)
        {
            return QFE_TIMEOUT;
        }
    }
    memcpy(config, &current_fpe_config, sizeof(QuestFitfpe_config_response_t));
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_sendFpeConfigOnly(QuestFitfpe_config_request_t *config, char *serialNumber)
{
    if (!QuestFitNetworkComm_is_connected())
    {
        return QFE_NOT_CONNECTED;
    }
    // Send the multiple messages
    char fpeConfigTopic[100] = "";
    sprintf_s(fpeConfigTopic, sizeof(fpeConfigTopic), "fpe/%s/config/request", serialNumber);
    // Create config request
    QuestFitNetworkComm_publish_message(fpeConfigTopic, config, sizeof(QuestFitfpe_config_request_t));
    Sleep(200);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_sendFpeConfigLut(QuestFitfpe_ct_lut_t *lut_request, char *serialNumber)
{
    char fpeLutTopic[100] = "";
    sprintf_s(fpeLutTopic, sizeof(fpeLutTopic), "fpe/%s/ct_lut/request", serialNumber);

    QuestFitNetworkComm_publish_message(fpeLutTopic, lut_request, sizeof(QuestFitfpe_ct_lut_t));
    Sleep(200);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_sendFpeConfigLcCal(QuestFitfpe_lc_cal_t *lc_cal_request, char *serialNumber)
{
    char fpeLcTopic[100] = "";
    sprintf_s(fpeLcTopic, sizeof(fpeLcTopic), "fpe/%s/lc_cal/request", serialNumber);
    QuestFitNetworkComm_publish_message(fpeLcTopic, lc_cal_request, sizeof(QuestFitfpe_lc_cal_t));
    Sleep(200);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_sendFpeConfigReordering(QuestFitfpe_reordering_t *reorder_request, char *serialNumber)
{
    char fpeReorderTopic[100] = "";
    sprintf_s(fpeReorderTopic, sizeof(fpeReorderTopic), "fpe/%s/reordering/request", serialNumber);
    QuestFitNetworkComm_publish_message(fpeReorderTopic, reorder_request, sizeof(QuestFitfpe_reordering_t));
    Sleep(200);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_sendFpeConfigPolarity(QuestFitfpe_polarity_t *polarity_request, char *serialNumber)
{
    char fpePolarityTopic[100] = "";
    sprintf_s(fpePolarityTopic, sizeof(fpePolarityTopic), "fpe/%s/polarity/request", serialNumber);
    QuestFitNetworkComm_publish_message(fpePolarityTopic, polarity_request, sizeof(QuestFitfpe_polarity_t));
    Sleep(200);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_sendFpeConfig(QuestFitfpe_config_response_t *config, char *serialNumber)
{
    if (!QuestFitNetworkComm_is_connected())
    {
        return QFE_NOT_CONNECTED;
    }
    // Send the multiple messages
    char fpeConfigTopic[100] = "";
    sprintf_s(fpeConfigTopic, sizeof(fpeConfigTopic), "fpe/%s/config/request", serialNumber);
    // Create config request
    QuestFitfpe_config_request_t config_request = {
        .setParameterFlags = 0xFFFFFFFF, // Set ALL values
        .OperatingMode = config->OperatingMode,
        .SystemIndex = config->SystemIndex,
        .TypeIndicator = config->TypeIndicator,
        .OriginX = config->OriginX,
        .OriginY = config->OriginY,
        .OriginZ = config->OriginZ,
        .PlateXSize = config->PlateXSize,
        .PlateYSize = config->PlateYSize,
        .FxCapacity = config->FxCapacity,
        .FyCapacity = config->FyCapacity,
        .FzCapacity = config->FzCapacity,
        .OutputFormat = config->OutputFormat,
        .ActiveThreshold = config->ActiveThreshold,
        .GroupDelay = config->GroupDelay,
        .ExcitationVoltage = config->ExcitationVoltage,
        .XChannelGain = config->XChannelGain,
        .YChannelGain = config->YChannelGain,
        .ZChannelGain = config->ZChannelGain,
        .Resolution = config->Resolution,
        .XOffset = config->XOffset,
        .YOffset = config->YOffset,
        .ZOffsetVolts = config->ZOffsetVolts,
        .AutoTareEnable = config->AutoTareEnable};
    strncpy_s(config_request.FPE_ModelNumber, sizeof(config_request.FPE_ModelNumber), config->FPE_ModelNumber, _TRUNCATE);// sizeof(config->ModelNumber));
    strncpy_s(config_request.FPE_SerialNumber, sizeof(config_request.FPE_SerialNumber), config->FPE_SerialNumber, _TRUNCATE);// sizeof(config->SerialNumber));
    strncpy_s(config_request.FP_ModelNumber, sizeof(config_request.FP_ModelNumber), config->FP_ModelNumber, _TRUNCATE);// sizeof(config->ModelNumber));
    strncpy_s(config_request.FP_SerialNumber, sizeof(config_request.FP_SerialNumber), config->FP_SerialNumber, _TRUNCATE);// sizeof(config->SerialNumber));
    strncpy_s(config_request.FP_BoardName, sizeof(config_request.FP_BoardName), config->FP_BoardName, _TRUNCATE);// sizeof(config->SerialNumber));
    QuestFitNetworkInterface_sendFpeConfigOnly(&config_request, serialNumber);
    Sleep(1000);

    // Create the CT Messages
    QuestFitfpe_ct_lut_t lut_request = {0};
    // CT lut 1
    lut_request.tableNumber = 1;
    lut_request.CT_LUT_C1 = config->Fx1CTalkOnFy1;
    lut_request.CT_LUT_C2 = config->Fx1CTalkOnFz1;
    lut_request.CT_LUT_C3 = config->Fy1CTalkOnFx1;
    lut_request.CT_LUT_C4 = config->Fy1CTalkOnFz1;
    lut_request.CT_LUT_C5 = config->Fz1CTalkOnFx1;
    lut_request.CT_LUT_C6 = config->Fz1CTalkOnFy1;
    QuestFitNetworkInterface_sendFpeConfigLut(&lut_request, serialNumber);
    Sleep(1000);

    // CT lut 2
    lut_request.tableNumber = 2;
    lut_request.CT_LUT_C1 = config->Fx2CTalkOnFy2;
    lut_request.CT_LUT_C2 = config->Fx2CTalkOnFz2;
    lut_request.CT_LUT_C3 = config->Fy2CTalkOnFx2;
    lut_request.CT_LUT_C4 = config->Fy2CTalkOnFz2;
    lut_request.CT_LUT_C5 = config->Fz2CTalkOnFx2;
    lut_request.CT_LUT_C6 = config->Fz2CTalkOnFy2;
    QuestFitNetworkInterface_sendFpeConfigLut(&lut_request, serialNumber);
    Sleep(1000);

    // CT lut 3
    lut_request.tableNumber = 3;
    lut_request.CT_LUT_C1 = config->Fx3CTalkOnFy3;
    lut_request.CT_LUT_C2 = config->Fx3CTalkOnFz3;
    lut_request.CT_LUT_C3 = config->Fy3CTalkOnFx3;
    lut_request.CT_LUT_C4 = config->Fy3CTalkOnFz3;
    lut_request.CT_LUT_C5 = config->Fz3CTalkOnFx3;
    lut_request.CT_LUT_C6 = config->Fz3CTalkOnFy3;
    QuestFitNetworkInterface_sendFpeConfigLut(&lut_request, serialNumber);
    Sleep(1000);

    // CT lut 4
    lut_request.tableNumber = 4;
    lut_request.CT_LUT_C1 = config->Fx4CTalkOnFy4;
    lut_request.CT_LUT_C2 = config->Fx4CTalkOnFz4;
    lut_request.CT_LUT_C3 = config->Fy4CTalkOnFx4;
    lut_request.CT_LUT_C4 = config->Fy4CTalkOnFz4;
    lut_request.CT_LUT_C5 = config->Fz4CTalkOnFx4;
    lut_request.CT_LUT_C6 = config->Fz4CTalkOnFy4;
    QuestFitNetworkInterface_sendFpeConfigLut(&lut_request, serialNumber);
    Sleep(1000);


    QuestFitfpe_lc_cal_t lc_cal_request = {
        .Fx1mvPerVolt = config->Fx1mvPerVolt,
        .Fy1mvPerVolt = config->Fy1mvPerVolt,
        .Fz1mvPerVolt = config->Fz1mvPerVolt,

        .Fx2mvPerVolt = config->Fx2mvPerVolt,
        .Fy2mvPerVolt = config->Fy2mvPerVolt,
        .Fz2mvPerVolt = config->Fz2mvPerVolt,

        .Fx3mvPerVolt = config->Fx3mvPerVolt,
        .Fy3mvPerVolt = config->Fy3mvPerVolt,
        .Fz3mvPerVolt = config->Fz3mvPerVolt,

        .Fx4mvPerVolt = config->Fx4mvPerVolt,
        .Fy4mvPerVolt = config->Fy4mvPerVolt,
        .Fz4mvPerVolt = config->Fz4mvPerVolt,
    };
    QuestFitNetworkInterface_sendFpeConfigLcCal(&lc_cal_request, serialNumber);
    Sleep(1000);

    // Create the reordering Messages
    QuestFitfpe_reordering_t reorder_request = {0};
    memcpy(reorder_request.ChannelOrder, config->ChannelOrder, sizeof(reorder_request.ChannelOrder));
    QuestFitNetworkInterface_sendFpeConfigReordering(&reorder_request, serialNumber);
    Sleep(1000);


    QuestFitfpe_polarity_t polarity_request = {
        .Fx1Polarity = config->Fx1Polarity,
        .Fy1Polarity = config->Fy1Polarity,
        .Fz1Polarity = config->Fz1Polarity,

        .Fx2Polarity = config->Fx2Polarity,
        .Fy2Polarity = config->Fy2Polarity,
        .Fz2Polarity = config->Fz2Polarity,

        .Fx3Polarity = config->Fx3Polarity,
        .Fy3Polarity = config->Fy3Polarity,
        .Fz3Polarity = config->Fz3Polarity,

        .Fx4Polarity = config->Fx4Polarity,
        .Fy4Polarity = config->Fy4Polarity,
        .Fz4Polarity = config->Fz4Polarity,
    };
    QuestFitNetworkInterface_sendFpeConfigPolarity(&polarity_request, serialNumber);
    Sleep(1000);
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_sendPlatformUpdate(char *path)
{
    // Check to see if file exists
    if (access(path, F_OK) != 0)
    {
        return QFE_FILE_NOT_FOUND;
    }
    // Get file length
    FILE *filePtr = fopen(path, "rb");
    fseek(filePtr, 0, SEEK_END);
    long fileLength = ftell(filePtr);
    rewind(filePtr);
    if (fileLength > MAX_FILE_SIZE)
    {
        return QFE_FILE_TOO_LONG;
    }

    // Allocate memory for file buffer
    char *fileBuf = (char *)malloc(fileLength * sizeof(char));
    fread(fileBuf, fileLength, 1, filePtr);
    fclose(filePtr);

    QuestFitNetworkComm_publish_message("pe/update/request", fileBuf, fileLength);
    free(fileBuf);

    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_sendCalibrationFile(char *path, char *serial)
{
    // Check to see if file exists
    if (access(path, F_OK) != 0)
    {
        return QFE_FILE_NOT_FOUND;
    }
    // Get file length
    FILE *filePtr = fopen(path, "rb");
    fseek(filePtr, 0, SEEK_END);
    long fileLength = ftell(filePtr);
    rewind(filePtr);

    // Allocate memory for file buffer
    char *fileBuf = (char *)malloc(fileLength * sizeof(char));
    fread(fileBuf, fileLength, 1, filePtr);
    fclose(filePtr);

    char fpeCommandTopic[100] = "";
    sprintf_s(fpeCommandTopic, sizeof(fpeCommandTopic), "fpe/%s/calFile/request", serial);
    QuestFitNetworkComm_publish_message(fpeCommandTopic, fileBuf, fileLength);
    current_cal_progress_number = 0;

    free(fileBuf);

    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_setCalibrationProgress(int32_t progress, char *serial)
{
    current_cal_progress_number = progress;
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_getCalibrationProgress(int32_t *progress, char *serial)
{
    *progress = current_cal_progress_number;
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_storeDebugSample(QuestFitdebug_sample_t *sample, char *serial)
{
    // Check to see if this serial number is the current device
    if (!strcmp(serial, currentDebugSerialNumber) && debug_circular_buffer != NULL)
    {
        // Add the sample to the buffer
        QuestFitCircularBuffer_put(debug_circular_buffer, sample);
    }
    else{
        elogError("Got samples from invalid serial number %s", serial);
    }
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_clearDebugSamples()
{
    if(debug_circular_buffer != NULL)
    {
        QuestFitCircularBuffer_reset(debug_circular_buffer);
        return QFE_OK;
    }
    return QFE_NOT_CONNECTED;
}
QuestFitError_e QuestFitNetworkInterface_getDebugSamples(QuestFitdebug_sample_t *samples, char *serialNumber, size_t maxSampleCount, size_t *data_retrieved, bool waitForFull)
{
    // Check to see if this serial number is the current device
    if (!strcmp(serialNumber, currentDebugSerialNumber) && debug_circular_buffer != NULL)
    {
        if (!QuestFitNetworkComm_is_connected())
        {
            return QFE_NOT_CONNECTED;
        }
        QuestFitCircularBuffer_getAvailable(debug_circular_buffer, maxSampleCount, data_retrieved);
        if (waitForFull && *data_retrieved < maxSampleCount)
        {
            return QFE_NOT_ENOUGH_DATA;
        }
        // Attempt to get the count of samples from the buffer
        QuestFitCircularBuffer_get(debug_circular_buffer, (uint8_t *)samples, maxSampleCount, data_retrieved);
    }
    else{
        elogError("Got samples from invalid serial number %s", serialNumber);
    }
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_startDebugMode(char *serialNumber)
{
    elogInfo("Starting debug mode for %s", serialNumber);
    QuestFitCircularBuffer_init(DEBUG_DATA_SAMPLE_COUNT, sizeof(QuestFitdebug_sample_t), &debug_circular_buffer);
    strncpy(currentDebugSerialNumber, serialNumber, sizeof(currentDebugSerialNumber));
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_stopDebugMode(char *serialNumber)
{
    void *tmp_buf_addr = debug_circular_buffer;
    debug_circular_buffer = NULL;
    QuestFitCircularBuffer_free(tmp_buf_addr);
    memset(currentDebugSerialNumber, 0, sizeof(currentDebugSerialNumber));
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_setTestNumber(int number)
{
    current_test_number = number;

    post_sem(testNumSemaphore);
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_getTestNumber(int *number, bool blockForUpdate)
{
    if (QuestFitNetworkComm_is_connected() && *number != -1)
    {
        char buf[50];
        sprintf(buf, "%d", *number);
        QuestFitNetworkComm_publish_message("testbn123/setNumber", buf, strlen(buf));
        if (wait_for_sem(testNumSemaphore) == QFE_TIMEOUT)
        {
            return QFE_TIMEOUT;
        }
    }

    *number = current_test_number;
    return QFE_OK;
}

QuestFitError_e QuestFitNetworkInterface_Initialize()
{
#ifdef _MSC_VER
    peConfigSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
    peStatusSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
    fpeEnumerationSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
    fpeStatusSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
    fpeConfigSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
    testNumSemaphore = CreateSemaphore(NULL, 0, 1, NULL);
#endif
    if (QuestFitNetworkComm_connect() != 0)
    {
        return QFE_TIMEOUT;
    }
    return QFE_OK;
}
QuestFitError_e QuestFitNetworkInterface_Destroy()
{
    QuestFitNetworkComm_Destroy();
    return QFE_OK;
}