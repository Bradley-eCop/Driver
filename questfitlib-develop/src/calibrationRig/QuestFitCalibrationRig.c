#include "QuestFitCalibrationRig.h"
#include "QuestFitNetworkInterface.h"
#include <string.h>
#include <stdlib.h>
#include "eLog.h"
#include <windows.h>


#define NUM_SAMPLE_MAX 8000
static char currentSerialNumber[65] = {0};
// #define MOCK_DATA
#ifdef MOCK_DATA
char MOCK_DATA_SERIAL[10] ="123";
#endif

__declspec(dllexport) QuestFitCalibrationRigError_e QuestFitCalibrationRig_InitDataMode()
{
    // Get current configuration
    QuestFitfpe_enumeration_t enumeration;
    QuestFitpe_config_t config = {0};
    int retry = 5;
    while (retry--)
    {
#ifdef MOCK_DATA
        memset(enumeration.serial_number[0], 0, sizeof(enumeration.serial_number[0]));
        strncpy(enumeration.serial_number[0], MOCK_DATA_SERIAL, strlen(MOCK_DATA_SERIAL));
#else
        if (QuestFitNetworkInterface_getFpeEnumeration(&enumeration, true) != QFE_OK)
        {
            Sleep(1000);
            continue;
        }
#endif
        QuestFitNetworkInterface_initializePeConfig(&config);
        // Enable raw data mode on the first connected FPE
        strncpy(config.fpe_list[0].serial_number, enumeration.serial_number[0], sizeof(enumeration.serial_number[0]));
        strncpy(currentSerialNumber, enumeration.serial_number[0], sizeof(enumeration.serial_number[0]));
        config.fpe_list[0].enabled = true;
        config.fpe_list[0].operating_mode = QUESTFIT_FPE_MODE_DEBUG;
        config.mode = QUESTFIT_MODE_IDLE;
#ifdef MOCK_DATA
        config.sim_enabled = 1;
#endif
        config.sample_rate_hz = 2000;

        if (QuestFitNetworkInterface_sendPeConfig(&config) != QFE_OK)
        {
            Sleep(1000);
            continue;
        }
        return QFCR_OK;
    }
    elogError("Start Raw Data Command Timed Out");
    return QFCR_TIMEOUT;
}
__declspec(dllexport) QuestFitCalibrationRigError_e QuestFitCalibrationRig_StartCapture(double sampleRate)
{
    // Get current configuration
    QuestFitfpe_enumeration_t enumeration;
    QuestFitpe_config_t config = {0};
    elogInfo("Trying to start debug capture at %lf", sampleRate);
    int retry = 5;
    while (retry--)
    {
#ifdef MOCK_DATA
        memset(enumeration.serial_number[0], 0, sizeof(enumeration.serial_number[0]));
        strncpy(enumeration.serial_number[0], MOCK_DATA_SERIAL, strlen(MOCK_DATA_SERIAL));
#else
        if (QuestFitNetworkInterface_getFpeEnumeration(&enumeration, true) != QFE_OK)
        {
            Sleep(1000);
            continue;
        }
#endif
        QuestFitNetworkInterface_initializePeConfig(&config);
        // Enable raw data mode on the first connected FPE
        strncpy(config.fpe_list[0].serial_number, enumeration.serial_number[0], sizeof(enumeration.serial_number[0]));
        strncpy(currentSerialNumber, enumeration.serial_number[0], sizeof(enumeration.serial_number[0]));
        config.fpe_list[0].enabled = true;
        config.fpe_list[0].operating_mode = QUESTFIT_FPE_MODE_DEBUG;
        config.mode = QUESTFIT_MODE_FREE_RUN;
#ifdef MOCK_DATA
        config.sim_enabled = 1;
#endif
        config.sample_rate_hz = (uint16_t) sampleRate;

        if (QuestFitNetworkInterface_sendPeConfig(&config) != QFE_OK)
        {
            Sleep(1000);
            continue;
        }
        // Enable raw data in the interface driver
        QuestFitNetworkInterface_startDebugMode(currentSerialNumber);
        return QFCR_OK;
    }
    elogError("Start Raw Data Command Timed Out");
    return QFCR_TIMEOUT;
}

__declspec(dllexport) QuestFitCalibrationRigError_e QuestFitCalibrationRig_StopCapture()
{
    // Get current configuration
    QuestFitfpe_enumeration_t enumeration;
    QuestFitpe_config_t config = {0};
    int retry = 5;
    while (retry--)
    {
#ifdef MOCK_DATA
        memset(enumeration.serial_number[0], 0, sizeof(enumeration.serial_number[0]));

        strncpy(enumeration.serial_number[0], MOCK_DATA_SERIAL, strlen(MOCK_DATA_SERIAL));
#else
        if (QuestFitNetworkInterface_getFpeEnumeration(&enumeration, true) != QFE_OK)
        {
            Sleep(1000);
            continue;
        }
#endif
        QuestFitNetworkInterface_initializePeConfig(&config);
        // Enable raw data mode on the first connected FPE
        strncpy(config.fpe_list[0].serial_number, enumeration.serial_number[0], sizeof(enumeration.serial_number[0]));
        strncpy(currentSerialNumber, enumeration.serial_number[0], sizeof(enumeration.serial_number[0]));
        config.fpe_list[0].enabled = true;
        config.fpe_list[0].operating_mode = QUESTFIT_FPE_MODE_DEBUG;
        config.mode = QUESTFIT_MODE_IDLE;
#ifdef MOCK_DATA
        config.sim_enabled = 1;
#endif
        config.sample_rate_hz = 2000;

        if (QuestFitNetworkInterface_sendPeConfig(&config) != QFE_OK)
        {
            Sleep(1000);
            continue;
        }
        // Disable raw data in the interface driver
        // if (QuestFitNetworkInterface_stopDebugMode(currentSerialNumber) != QFE_OK)
        //     continue;
        return QFCR_OK;
    }
    elogError("Start Raw Data Command Timed Out");
    return QFCR_TIMEOUT;
}
__declspec(dllexport) QuestFitCalibrationRigError_e QuestFitCalibrationRig_DeInitDataMode()
{
    // Get current configuration
    QuestFitpe_config_t config = {0};
    QuestFitfpe_enumeration_t enumeration;
    int retry = 5;
    while (retry--)
    {
        if (QuestFitNetworkInterface_getFpeEnumeration(&enumeration, true) != QFE_OK)
        {
            Sleep(1000);
            continue;
        }
        QuestFitNetworkInterface_initializePeConfig(&config);
        strncpy(currentSerialNumber, enumeration.serial_number[0], sizeof(enumeration.serial_number[0]));
        config.fpe_list[0].enabled = true;
        config.fpe_list[0].operating_mode = QUESTFIT_FPE_MODE_DEBUG;
        if (QuestFitNetworkInterface_sendPeConfig(&config) != QFE_OK)
            continue;
        return QFCR_OK;
    }
    elogError("Stop Raw Data Command Timed Out");
    return QFCR_TIMEOUT;
}
__declspec(dllexport) QuestFitCalibrationRigError_e QuestFitCalibrationRig_ClearSamples()
{
    return QuestFitNetworkInterface_clearDebugSamples();

}
__declspec(dllexport) QuestFitCalibrationRigError_e QuestFitCalibrationRig_GetSamples(size_t numSamples, QuestFitCalibrationSampleInterface_t *sampleBuffer, size_t *samplesOut)
{
    // Check inputs
    if (numSamples > NUM_SAMPLE_MAX)
    {
        return QFE_INVALID_LEN;
    }
    *samplesOut = 0;
    // Create buffer for samples
    QuestFitdebug_sample_t *samples = malloc(numSamples * sizeof(QuestFitdebug_sample_t));

    // Retrieve up to numSamples from the network interface
    QuestFitError_e result = QuestFitNetworkInterface_getDebugSamples(samples, currentSerialNumber, numSamples, samplesOut, true);
    if (result != QFE_OK)
    {
        free(samples);
        return result;
    }
    for (size_t i = 0; i < *samplesOut; i++)
    {
        QuestFitCalibrationSampleInterface_t *currentOutSample = &sampleBuffer[i];
        QuestFitdebug_sample_t *currentInSample = &samples[i];

        currentOutSample->Fx12 = currentInSample->Fx12;
        currentOutSample->Fx34 = currentInSample->Fx34;
        currentOutSample->Fy14 = currentInSample->Fy14;
        currentOutSample->Fy23 = currentInSample->Fy23;
        currentOutSample->Fz1 = currentInSample->Fz1;
        currentOutSample->Fz2 = currentInSample->Fz2;
        currentOutSample->Fz3 = currentInSample->Fz3;
        currentOutSample->Fz4 = currentInSample->Fz4;

        currentOutSample->Fx = currentInSample->Fx;
        currentOutSample->Fy = currentInSample->Fy;
        currentOutSample->Fz = currentInSample->Fz;

        currentOutSample->Mx = currentInSample->Mx;
        currentOutSample->My = currentInSample->My;
        currentOutSample->Mz = currentInSample->Mz;
    }
    free(samples);
    return QFE_OK;
}
__declspec(dllexport) extern QuestFitCalibrationRigError_e QuestFitCalibrationRig_Init()
{
    if(QuestFitNetworkInterface_Initialize() == QFE_OK){
        return QuestFitCalibrationRig_InitDataMode();
    }
    return QFE_NOT_CONNECTED;
}
__declspec(dllexport) extern QuestFitCalibrationRigError_e QuestFitCalibrationRig_Destroy()
{
    QuestFitCalibrationRig_DeInitDataMode();
    QuestFitNetworkInterface_Destroy();
    return QFE_NOT_CONNECTED;
}
