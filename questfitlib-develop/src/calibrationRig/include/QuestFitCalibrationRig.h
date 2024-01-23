/**
 * Calibration rig interface
 */
#ifndef QFCALRIG_H
#define QFCALRIG_H
#include <stdint.h>

typedef struct QuestFitCalibrationInterface_s
{
    float Fx12;
    float Fx34;
    float Fy14;
    float Fy23;
    float Fz1;
    float Fz2;
    float Fz3;
    float Fz4;
    float Fx;
    float Fy;
    float Fz;
    float Mx;
    float My;
    float Mz;

} QuestFitCalibrationSampleInterface_t;

typedef enum
{
    QFCR_OK = 0,
    QFCR_TIMEOUT,
    QFCR_NOT_CONNECTED,
    QFCR_INVALID_LEN,
    QCR_FILE_NOT_FOUND,
    QCR_NOT_ENOUGH_DATA,
} QuestFitCalibrationRigError_e;

__declspec(dllexport) extern QuestFitCalibrationRigError_e QuestFitCalibrationRig_StartCapture(double sampleRate);
__declspec(dllexport) extern QuestFitCalibrationRigError_e QuestFitCalibrationRig_StopCapture();
__declspec(dllexport) extern QuestFitCalibrationRigError_e QuestFitCalibrationRig_ClearSamples();
__declspec(dllexport) extern QuestFitCalibrationRigError_e QuestFitCalibrationRig_GetSamples(size_t numSamples, QuestFitCalibrationSampleInterface_t *sampleBuffer, size_t *samplesOut);
__declspec(dllexport) extern QuestFitCalibrationRigError_e QuestFitCalibrationRig_Init();
__declspec(dllexport) extern QuestFitCalibrationRigError_e QuestFitCalibrationRig_Destroy();

#endif // QFCALRIG_H