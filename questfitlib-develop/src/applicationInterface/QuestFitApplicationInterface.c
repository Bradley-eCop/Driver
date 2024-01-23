#include "QuestFitNetworkTypes.h"
#include "QuestFitInstrumentDriver.h"
#include "QuestFitApplicationInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef _MSC_VER
#include <windows.h>
#endif

__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_GetPeStatus(QuestFitApplicationInterface_pe_status_t *status)
{
    QuestFitpe_status_t *tmpStatus = malloc(sizeof(QuestFitpe_status_t));
    QuestFitError_e result = QuestFitInstrumentDriver_pe_get_status(tmpStatus);
    if (result == QFE_OK)
    {
        // Translate to app interface type
        status->state = tmpStatus->state;
        status->status = tmpStatus->status;
        status->sw_version_major = tmpStatus->sw_version_major;
        status->sw_version_minor = tmpStatus->sw_version_minor;
        status->sw_revision = tmpStatus->sw_revision;
    }
    free(tmpStatus);

    return result;
}

__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_GetFPEEnumeration(QuestFitApplicationInterface_fpe_enumeration_t *enumeration)
{
    QuestFitfpe_enumeration_t *tmpEnumeration = malloc(sizeof(QuestFitfpe_enumeration_t));
    QuestFitError_e result = QuestFitInstrumentDriver_fpe_get_enumeration(tmpEnumeration);
    if (result == QFE_OK)
    {
        // Translate to app interface type
        enumeration->count = tmpEnumeration->count;
        memcpy(enumeration->serial_number, tmpEnumeration->serial_number, sizeof(enumeration->serial_number));
    }
    free(tmpEnumeration);

    return result;
}
__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_GetFPEStatus(QuestFitApplicationInterface_fpe_status_t *status, char *serial)
{
    QuestFitfpe_status_response_t *tmpStatus = malloc(sizeof(QuestFitfpe_status_response_t));
    QuestFitError_e result = QuestFitInstrumentDriver_fpe_get_status(tmpStatus, serial);
    if (result == QFE_OK)
    {
        // Translate to app interface type
        status->state = tmpStatus->state;
        status->status = tmpStatus->status;
        status->missed_samples = tmpStatus->missed_samples;
        status->sw_version_major = tmpStatus->sw_version_major;
        status->sw_version_minor = tmpStatus->sw_version_minor;
        status->sw_revision = tmpStatus->sw_revision;
    }
    free(tmpStatus);

    return result;
}
__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_GetFPEInfo(QuestFitApplicationInterface_fpe_info_t *fpeInfo, char *serial)
{

    QuestFitfpe_config_response_t *tmpConfig = malloc(sizeof(QuestFitfpe_config_response_t));
    QuestFitError_e result = QuestFitInstrumentDriver_fpe_get_configuration(tmpConfig, serial);
    if (result == QFE_OK)
    {
        // strcpy(fpeInfo->boardName, "New Board Name");
        memcpy(fpeInfo->fpeSerialNumber, tmpConfig->FPE_SerialNumber, sizeof(fpeInfo->fpeSerialNumber));
        memcpy(fpeInfo->fpeModelNumber, tmpConfig->FPE_ModelNumber, sizeof(fpeInfo->fpeModelNumber));
        memcpy(fpeInfo->fpSerialNumber, tmpConfig->FP_SerialNumber, sizeof(fpeInfo->fpSerialNumber));
        memcpy(fpeInfo->fpModelNumber, tmpConfig->FP_ModelNumber, sizeof(fpeInfo->fpModelNumber));
        memcpy(fpeInfo->fpBoardName, tmpConfig->FP_BoardName, sizeof(fpeInfo->fpBoardName));

        QuestFitfpe_status_response_t *tmpStatus = malloc(sizeof(QuestFitfpe_status_response_t));
        result = QuestFitInstrumentDriver_fpe_get_status(tmpStatus, serial);
        if (result == QFE_OK)
        {
            sprintf_s(fpeInfo->firmwareRevision, sizeof(fpeInfo->firmwareRevision), "%d.%d.%d", tmpStatus->sw_version_major, tmpStatus->sw_version_minor, tmpStatus->sw_revision);
        }
        free(tmpStatus);
    }
    free(tmpConfig);
    return result;
}
__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_GetFPEDAQ(QuestFitApplicationInterface_fpe_daq_t *fpeDaq, char *serial)
{
    fpeDaq->excitationVoltage = 0;
    fpeDaq->voltageRange = 0;
    fpeDaq->xChannelGain = 0;
    fpeDaq->yChannelGain = 0;
    fpeDaq->zChannelGain = 0;
    fpeDaq->zOffsetVolts = 0;
    fpeDaq->resolution = 0;
    fpeDaq->sampleRate = 0;

    QuestFitfpe_config_response_t *tmpConfig = malloc(sizeof(QuestFitfpe_config_response_t));
    QuestFitError_e result = QuestFitInstrumentDriver_fpe_get_configuration(tmpConfig, serial);
    if (result == QFE_OK)
    {
        fpeDaq->excitationVoltage = tmpConfig->ExcitationVoltage;
        fpeDaq->voltageRange = tmpConfig->VoltageRange;
        fpeDaq->xChannelGain = tmpConfig->XChannelGain;
        fpeDaq->yChannelGain = tmpConfig->YChannelGain;
        fpeDaq->zChannelGain = tmpConfig->ZChannelGain;
        fpeDaq->zOffsetVolts = tmpConfig->ZOffsetVolts;
        fpeDaq->resolution = tmpConfig->Resolution;
        QuestFitpe_config_t *tmpPeConfig = malloc(sizeof(QuestFitpe_config_t));
        result = QuestFitInstrumentDriver_pe_get_config(tmpPeConfig);
        if (result == QFE_OK)
        {
            fpeDaq->sampleRate = tmpPeConfig->sample_rate_hz;
        }
        free(tmpPeConfig);
    }
    free(tmpConfig);
    return result;
}
__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_GetFPEPlate(QuestFitApplicationInterface_fpe_plate_t *fpePlate, char *serial)
{
    fpePlate->Index = 0;
    fpePlate->Type = 0;
    fpePlate->Origin[0] = 0;
    fpePlate->Origin[1] = 0;
    fpePlate->Origin[2] = 0;
    fpePlate->Offset[0] = 0;
    fpePlate->Offset[1] = 0;
    fpePlate->Offset[2] = 0;
    fpePlate->Size[0] = 0;
    fpePlate->Size[1] = 0;
    fpePlate->ChannelCapacity[0] = 0;
    fpePlate->ChannelCapacity[1] = 0;
    fpePlate->ChannelCapacity[2] = 0;
    fpePlate->ChannelCapacity[3] = 0;
    fpePlate->ChannelCapacity[4] = 0;
    fpePlate->ChannelCapacity[5] = 0;
    fpePlate->ActiveThreshold = 0;
    // TODO fpePlate->TaredValues
    fpePlate->OperatingMode = 0;
    fpePlate->OutputFormat = 0;
    fpePlate->GroupDelay = 0;
    QuestFitfpe_config_response_t *tmpConfig = malloc(sizeof(QuestFitfpe_config_response_t));
    QuestFitError_e result = QuestFitInstrumentDriver_fpe_get_configuration(tmpConfig, serial);
    if (result == QFE_OK)
    {
        fpePlate->Index = tmpConfig->SystemIndex;
        fpePlate->Type = tmpConfig->TypeIndicator;
        fpePlate->Origin[0] = tmpConfig->OriginX;
        fpePlate->Origin[1] = tmpConfig->OriginY;
        fpePlate->Origin[2] = tmpConfig->OriginZ;
        fpePlate->Offset[0] = tmpConfig->XOffset;
        fpePlate->Offset[1] = tmpConfig->YOffset;
        fpePlate->Offset[2] = tmpConfig->ZOffsetVolts;
        fpePlate->Size[0] = tmpConfig->PlateXSize;
        fpePlate->Size[1] = tmpConfig->PlateYSize;
        fpePlate->ChannelCapacity[0] = tmpConfig->ChannelCapacity[0];
        fpePlate->ChannelCapacity[1] = tmpConfig->ChannelCapacity[1];
        fpePlate->ChannelCapacity[2] = tmpConfig->ChannelCapacity[2];
        fpePlate->ChannelCapacity[3] = tmpConfig->ChannelCapacity[3];
        fpePlate->ChannelCapacity[4] = tmpConfig->ChannelCapacity[4];
        fpePlate->ChannelCapacity[5] = tmpConfig->ChannelCapacity[5];
        fpePlate->ActiveThreshold = tmpConfig->ActiveThreshold;
        // TODO fpePlate->TaredValues
        fpePlate->OperatingMode = tmpConfig->OperatingMode;
        fpePlate->OutputFormat = tmpConfig->OutputFormat;
        fpePlate->GroupDelay = tmpConfig->GroupDelay;
    }
    free(tmpConfig);
    return result;
}
__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_GetFPESensor(QuestFitApplicationInterface_fpe_sensor_t *fpeSensor, char *serial)
{
    QuestFitfpe_config_response_t *tmpConfig = malloc(sizeof(QuestFitfpe_config_response_t));
    QuestFitError_e result = QuestFitInstrumentDriver_fpe_get_configuration(tmpConfig, serial);
    if (result == QFE_OK)
    {
        fpeSensor->FxCapacity = tmpConfig->FxCapacity;
        fpeSensor->FyCapacity = tmpConfig->FyCapacity;
        fpeSensor->FzCapacity = tmpConfig->FzCapacity;
        fpeSensor->Fx1mvPerVolt = tmpConfig->Fx1mvPerVolt;
        fpeSensor->Fy1mvPerVolt = tmpConfig->Fy1mvPerVolt;
        fpeSensor->Fz1mvPerVolt = tmpConfig->Fz1mvPerVolt;

        fpeSensor->Fx2mvPerVolt = tmpConfig->Fx2mvPerVolt;
        fpeSensor->Fy2mvPerVolt = tmpConfig->Fy2mvPerVolt;
        fpeSensor->Fz2mvPerVolt = tmpConfig->Fz2mvPerVolt;

        fpeSensor->Fx3mvPerVolt = tmpConfig->Fx3mvPerVolt;
        fpeSensor->Fy3mvPerVolt = tmpConfig->Fy3mvPerVolt;
        fpeSensor->Fz3mvPerVolt = tmpConfig->Fz3mvPerVolt;

        fpeSensor->Fx4mvPerVolt = tmpConfig->Fx4mvPerVolt;
        fpeSensor->Fy4mvPerVolt = tmpConfig->Fy4mvPerVolt;
        fpeSensor->Fz4mvPerVolt = tmpConfig->Fz4mvPerVolt;

        fpeSensor->Fx1CTalkOnFy1 = tmpConfig->Fx1CTalkOnFy1;
        fpeSensor->Fx1CTalkOnFz1 = tmpConfig->Fx1CTalkOnFz1;
        fpeSensor->Fy1CTalkOnFx1 = tmpConfig->Fy1CTalkOnFx1;
        fpeSensor->Fy1CTalkOnFz1 = tmpConfig->Fy1CTalkOnFz1;
        fpeSensor->Fz1CTalkOnFx1 = tmpConfig->Fz1CTalkOnFx1;
        fpeSensor->Fz1CTalkOnFy1 = tmpConfig->Fz1CTalkOnFy1;
        fpeSensor->Fx2CTalkOnFy2 = tmpConfig->Fx2CTalkOnFy2;
        fpeSensor->Fx2CTalkOnFz2 = tmpConfig->Fx2CTalkOnFz2;
        fpeSensor->Fy2CTalkOnFx2 = tmpConfig->Fy2CTalkOnFx2;
        fpeSensor->Fy2CTalkOnFz2 = tmpConfig->Fy2CTalkOnFz2;
        fpeSensor->Fz2CTalkOnFx2 = tmpConfig->Fz2CTalkOnFx2;
        fpeSensor->Fz2CTalkOnFy2 = tmpConfig->Fz2CTalkOnFy2;
        fpeSensor->Fx3CTalkOnFy3 = tmpConfig->Fx3CTalkOnFy3;
        fpeSensor->Fx3CTalkOnFz3 = tmpConfig->Fx3CTalkOnFz3;
        fpeSensor->Fy3CTalkOnFx3 = tmpConfig->Fy3CTalkOnFx3;
        fpeSensor->Fy3CTalkOnFz3 = tmpConfig->Fy3CTalkOnFz3;
        fpeSensor->Fz3CTalkOnFx3 = tmpConfig->Fz3CTalkOnFx3;
        fpeSensor->Fz3CTalkOnFy3 = tmpConfig->Fz3CTalkOnFy3;
        fpeSensor->Fx4CTalkOnFy4 = tmpConfig->Fx4CTalkOnFy4;
        fpeSensor->Fx4CTalkOnFz4 = tmpConfig->Fx4CTalkOnFz4;
        fpeSensor->Fy4CTalkOnFx4 = tmpConfig->Fy4CTalkOnFx4;
        fpeSensor->Fy4CTalkOnFz4 = tmpConfig->Fy4CTalkOnFz4;
        fpeSensor->Fz4CTalkOnFx4 = tmpConfig->Fz4CTalkOnFx4;
        fpeSensor->Fz4CTalkOnFy4 = tmpConfig->Fz4CTalkOnFy4;

        fpeSensor->ChannelPolarity[0] = tmpConfig->Fx1Polarity;
        fpeSensor->ChannelPolarity[1] = tmpConfig->Fy1Polarity;
        fpeSensor->ChannelPolarity[2] = tmpConfig->Fz1Polarity;

        fpeSensor->ChannelPolarity[3] = tmpConfig->Fx2Polarity;
        fpeSensor->ChannelPolarity[4] = tmpConfig->Fy2Polarity;
        fpeSensor->ChannelPolarity[5] = tmpConfig->Fz2Polarity;

        fpeSensor->ChannelPolarity[6] = tmpConfig->Fx3Polarity;
        fpeSensor->ChannelPolarity[7] = tmpConfig->Fy3Polarity;
        fpeSensor->ChannelPolarity[8] = tmpConfig->Fz3Polarity;

        fpeSensor->ChannelPolarity[9] = tmpConfig->Fx4Polarity;
        fpeSensor->ChannelPolarity[10] = tmpConfig->Fy4Polarity;
        fpeSensor->ChannelPolarity[11] = tmpConfig->Fz4Polarity;

        fpeSensor->AutoTareEnable = tmpConfig->AutoTareEnable;
        memcpy(fpeSensor->ChannelOrder, tmpConfig->ChannelOrder, sizeof(tmpConfig->ChannelOrder));
    }
    free(tmpConfig);
    return result;
}
__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_SetFPEInfo(QuestFitApplicationInterface_fpe_info_t *fpeInfo, char *serial)
{

    QuestFitfpe_config_request_t configRequest = {
        .setParameterFlags = SET_FPE_SERIAL_NUM | SET_FPE_MODEL_NUM | SET_FP_MODEL_NUM | SET_FP_SERIAL_NUM | SET_FP_BOARD_NAME};
    memcpy(configRequest.FPE_SerialNumber, fpeInfo->fpeSerialNumber, sizeof(fpeInfo->fpeSerialNumber));
    memcpy(configRequest.FPE_ModelNumber, fpeInfo->fpeModelNumber, sizeof(fpeInfo->fpeModelNumber));
    memcpy(configRequest.FP_SerialNumber, fpeInfo->fpSerialNumber, sizeof(fpeInfo->fpSerialNumber));
    memcpy(configRequest.FP_ModelNumber, fpeInfo->fpModelNumber, sizeof(fpeInfo->fpModelNumber));
    memcpy(configRequest.FP_BoardName, fpeInfo->fpBoardName, sizeof(fpeInfo->fpBoardName));
    QuestFitError_e result = QuestFitInstrumentDriver_fpe_send_ConfigOnly(&configRequest, serial);

    // Wait for status to return, indicating that this operation has completed
    QuestFitfpe_status_response_t *tmpStatus = malloc(sizeof(QuestFitfpe_status_response_t));
    result = QuestFitInstrumentDriver_fpe_get_status(tmpStatus, serial);
    free(tmpStatus);
    return result;
}
__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_SetFPEDAQ(QuestFitApplicationInterface_fpe_daq_t *fpeDaq, char *serial)
{

    QuestFitfpe_config_request_t configRequest = {
        .setParameterFlags = SET_EXCITATION_VOLTAGE | SET_VOLTAGE_RANGE | SET_X_CHANNEL_GAIN | SET_Y_CHANNEL_GAIN | SET_Z_CHANNEL_GAIN | SET_Z_OFFSET | SET_RESOLUTION,
        .ExcitationVoltage = fpeDaq->excitationVoltage,
        .VoltageRange = fpeDaq->voltageRange,
        .XChannelGain = fpeDaq->xChannelGain,
        .YChannelGain = fpeDaq->yChannelGain,
        .ZChannelGain = fpeDaq->zChannelGain,
        .ZOffsetVolts = fpeDaq->zOffsetVolts,
        .Resolution = fpeDaq->resolution,
    };
    QuestFitError_e result = QuestFitInstrumentDriver_fpe_send_ConfigOnly(&configRequest, serial);

    // Wait for status to return, indicating that this operation has completed
    QuestFitfpe_status_response_t *tmpStatus = malloc(sizeof(QuestFitfpe_status_response_t));
    result = QuestFitInstrumentDriver_fpe_get_status(tmpStatus, serial);
    free(tmpStatus);
    return result;
}
__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_SetFPEPlate(QuestFitApplicationInterface_fpe_plate_t *fpePlate, char *serial)
{
    QuestFitfpe_config_request_t configRequest = {
        .setParameterFlags = SET_LOCATION_NUM | SET_TYPE_INDICATOR | SET_ELE_ORIG_X | SET_ELE_ORIG_Y |
                             SET_ELE_ORIG_Z | SET_X_OFFSET | SET_Y_OFFSET | SET_WIDTH | SET_LENGTH |
                              SET_CALC_THRESHOLD | SET_OPERATING_MODE |
                             SET_OUTPUT_FORMAT | SET_GROUP_DELAY | SET_CHANNEL_CAPACITY,
        .SystemIndex = fpePlate->Index,
        .TypeIndicator = fpePlate->Type,
        .OriginX = fpePlate->Origin[0],
        .OriginY = fpePlate->Origin[1],
        .OriginZ = fpePlate->Origin[2],
        .XOffset = fpePlate->Offset[0],
        .YOffset = fpePlate->Offset[1],
        .PlateXSize = fpePlate->Size[0],
        .PlateYSize = fpePlate->Size[1],
        .ChannelCapacity[0] = fpePlate->ChannelCapacity[0],
        .ChannelCapacity[1] = fpePlate->ChannelCapacity[1],
        .ChannelCapacity[2] = fpePlate->ChannelCapacity[2],
        .ChannelCapacity[3] = fpePlate->ChannelCapacity[3],
        .ChannelCapacity[4] = fpePlate->ChannelCapacity[4],
        .ChannelCapacity[5] = fpePlate->ChannelCapacity[5],
        .ActiveThreshold = fpePlate->ActiveThreshold,
        .OperatingMode = fpePlate->OperatingMode,
        .OutputFormat = fpePlate->OutputFormat,
        .GroupDelay = fpePlate->GroupDelay,
    };
    QuestFitError_e result = QuestFitInstrumentDriver_fpe_send_ConfigOnly(&configRequest, serial);

    // Wait for status to return, indicating that this operation has completed
    QuestFitfpe_status_response_t *tmpStatus = malloc(sizeof(QuestFitfpe_status_response_t));
    result = QuestFitInstrumentDriver_fpe_get_status(tmpStatus, serial);
    free(tmpStatus);
    return result;
}
__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_SetFPESensor(QuestFitApplicationInterface_fpe_sensor_t *fpeSensor, char *serial)
{
    QuestFitfpe_lc_cal_t cal_request = {

        .Fx1mvPerVolt = fpeSensor->Fx1mvPerVolt,
        .Fy1mvPerVolt = fpeSensor->Fy1mvPerVolt,
        .Fz1mvPerVolt = fpeSensor->Fz1mvPerVolt,
        .Fx2mvPerVolt = fpeSensor->Fx2mvPerVolt,
        .Fy2mvPerVolt = fpeSensor->Fy2mvPerVolt,
        .Fz2mvPerVolt = fpeSensor->Fz2mvPerVolt,
        .Fx3mvPerVolt = fpeSensor->Fx3mvPerVolt,
        .Fy3mvPerVolt = fpeSensor->Fy3mvPerVolt,
        .Fz3mvPerVolt = fpeSensor->Fz3mvPerVolt,
        .Fx4mvPerVolt = fpeSensor->Fx4mvPerVolt,
        .Fy4mvPerVolt = fpeSensor->Fy4mvPerVolt,
        .Fz4mvPerVolt = fpeSensor->Fz4mvPerVolt,
    };
    QuestFitError_e result = QuestFitInstrumentDriver_fpe_send_configLcCal(&cal_request, serial);
    QuestFitfpe_ct_lut_t lut_request = {0};
    // CT lut 1
    lut_request.tableNumber = 1;
    lut_request.CT_LUT_C1 = fpeSensor->Fx1CTalkOnFy1;
    lut_request.CT_LUT_C2 = fpeSensor->Fx1CTalkOnFz1;
    lut_request.CT_LUT_C3 = fpeSensor->Fy1CTalkOnFx1;
    lut_request.CT_LUT_C4 = fpeSensor->Fy1CTalkOnFz1;
    lut_request.CT_LUT_C5 = fpeSensor->Fz1CTalkOnFx1;
    lut_request.CT_LUT_C6 = fpeSensor->Fz1CTalkOnFy1;
    result = QuestFitInstrumentDriver_fpe_send_configLut(&lut_request, serial);
    Sleep(500);

    // CT lut 2
    lut_request.tableNumber = 2;
    lut_request.CT_LUT_C1 = fpeSensor->Fx2CTalkOnFy2;
    lut_request.CT_LUT_C2 = fpeSensor->Fx2CTalkOnFz2;
    lut_request.CT_LUT_C3 = fpeSensor->Fy2CTalkOnFx2;
    lut_request.CT_LUT_C4 = fpeSensor->Fy2CTalkOnFz2;
    lut_request.CT_LUT_C5 = fpeSensor->Fz2CTalkOnFx2;
    lut_request.CT_LUT_C6 = fpeSensor->Fz2CTalkOnFy2;
    result = QuestFitInstrumentDriver_fpe_send_configLut(&lut_request, serial);
    Sleep(500);

    // CT lut 3
    lut_request.tableNumber = 3;
    lut_request.CT_LUT_C1 = fpeSensor->Fx3CTalkOnFy3;
    lut_request.CT_LUT_C2 = fpeSensor->Fx3CTalkOnFz3;
    lut_request.CT_LUT_C3 = fpeSensor->Fy3CTalkOnFx3;
    lut_request.CT_LUT_C4 = fpeSensor->Fy3CTalkOnFz3;
    lut_request.CT_LUT_C5 = fpeSensor->Fz3CTalkOnFx3;
    lut_request.CT_LUT_C6 = fpeSensor->Fz3CTalkOnFy3;
    result = QuestFitInstrumentDriver_fpe_send_configLut(&lut_request, serial);
    Sleep(500);

    // CT lut 4
    lut_request.tableNumber = 4;
    lut_request.CT_LUT_C1 = fpeSensor->Fx4CTalkOnFy4;
    lut_request.CT_LUT_C2 = fpeSensor->Fx4CTalkOnFz4;
    lut_request.CT_LUT_C3 = fpeSensor->Fy4CTalkOnFx4;
    lut_request.CT_LUT_C4 = fpeSensor->Fy4CTalkOnFz4;
    lut_request.CT_LUT_C5 = fpeSensor->Fz4CTalkOnFx4;
    lut_request.CT_LUT_C6 = fpeSensor->Fz4CTalkOnFy4;
    result = QuestFitInstrumentDriver_fpe_send_configLut(&lut_request, serial);
    Sleep(500);

    QuestFitfpe_polarity_t polarity_request = {

        .Fx1Polarity = fpeSensor->ChannelPolarity[0],
        .Fy1Polarity = fpeSensor->ChannelPolarity[1],
        .Fz1Polarity = fpeSensor->ChannelPolarity[2],

        .Fx2Polarity = fpeSensor->ChannelPolarity[3],
        .Fy2Polarity = fpeSensor->ChannelPolarity[4],
        .Fz2Polarity = fpeSensor->ChannelPolarity[5],

        .Fx3Polarity = fpeSensor->ChannelPolarity[6],
        .Fy3Polarity = fpeSensor->ChannelPolarity[7],
        .Fz3Polarity = fpeSensor->ChannelPolarity[8],

        .Fx4Polarity = fpeSensor->ChannelPolarity[9],
        .Fy4Polarity = fpeSensor->ChannelPolarity[10],
        .Fz4Polarity = fpeSensor->ChannelPolarity[11],
    };
    result = QuestFitInstrumentDriver_fpe_send_configPolarity(&polarity_request, serial);
    Sleep(500);

    QuestFitfpe_reordering_t reorder_request = {0};
    memcpy(reorder_request.ChannelOrder, fpeSensor->ChannelOrder, sizeof(reorder_request.ChannelOrder));
    result = QuestFitInstrumentDriver_fpe_send_configReordering(&reorder_request, serial);
    Sleep(500);

    QuestFitfpe_config_request_t configRequest = {
        .setParameterFlags = SET_FX_CAPACITY | SET_FY_CAPACITY | SET_FZ_CAPACITY | SET_AUTO_TARE_ENABLE,
        .AutoTareEnable = fpeSensor->AutoTareEnable,
        .FxCapacity = fpeSensor->FxCapacity,
        .FyCapacity = fpeSensor->FyCapacity,
        .FzCapacity = fpeSensor->FzCapacity,
    };
    result = QuestFitInstrumentDriver_fpe_send_ConfigOnly(&configRequest, serial);

    // Wait for status to return, indicating that this operation has completed
    QuestFitfpe_status_response_t *tmpStatus = malloc(sizeof(QuestFitfpe_status_response_t));
    result = QuestFitInstrumentDriver_fpe_get_status(tmpStatus, serial);
    free(tmpStatus);
    return result;
}
__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_SendPlatformUpdate(char *path)
{
    // Direct the instrument driver to start the file upload
    return QuestFitInstrumentDriver_pe_send_update(path);
}

__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_SendCalibrationFile(char *path, char *serial)
{
    // Direct the instrument driver to start the cal file upload
    return QuestFitInstrumentDriver_fpe_send_calibration(path, serial);
}

__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_GetCalibrationProgress(int32_t *progress, char *serial)
{
    return QuestFitInstrumentDriver_fpe_get_calibration_progress(progress, serial);
}

__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_Free(void *status)
{
    free(status);
    return QFE_OK;
}

__declspec(dllexport) QuestFitError_e QuestFitApplicationInterface_Initialize()
{
    // Initialize instrument driver
    QuestFitInstrumentDriver_Initialize();
    return QFE_OK;
}
