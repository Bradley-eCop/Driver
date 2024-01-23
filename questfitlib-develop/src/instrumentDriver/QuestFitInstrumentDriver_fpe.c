#include <stdbool.h>
#include "QuestFitInstrumentDriver_fpe.h"
#include "QuestFitNetworkInterface.h"
#define RETRY 5

QuestFitError_e QuestFitInstrumentDriver_fpe_get_enumeration(QuestFitfpe_enumeration_t *enumeration)
{
    return QuestFitNetworkInterface_getFpeEnumeration(enumeration, true);
}

QuestFitError_e QuestFitInstrumentDriver_fpe_get_status(QuestFitfpe_status_response_t *status, char* serial)
{
    int retry = RETRY;
    QuestFitError_e result;
    while (retry--)
    {
        result = QuestFitNetworkInterface_getFpeStatus(status, serial, true);
        if(result != QFE_OK)
            continue;
        else
            break;
    }
    return result;
}

QuestFitError_e QuestFitInstrumentDriver_fpe_get_configuration(QuestFitfpe_config_response_t *config, char* serial)
{
    int retry = RETRY;
    QuestFitError_e result;
    while (retry--)
    {
        result = QuestFitNetworkInterface_getFpeConfig(config, serial, true);
        if(result != QFE_OK)
            continue;
        else
            break;
    }
    return result;

}
QuestFitError_e QuestFitInstrumentDriver_fpe_send_configuration(QuestFitfpe_config_response_t *config, char* serial)
{
    int retry = RETRY;
    QuestFitError_e result;
    while (retry--)
    {
        result = QuestFitNetworkInterface_sendFpeConfig(config, serial);
        if(result != QFE_OK)
            continue;
        else
            break;
    }
    return result;

}
QuestFitError_e QuestFitInstrumentDriver_fpe_send_ConfigOnly(QuestFitfpe_config_request_t *config, char *serial)
{
    int retry = RETRY;
    QuestFitError_e result;
    while (retry--)
    {
        result = QuestFitNetworkInterface_sendFpeConfigOnly(config, serial);
        if(result != QFE_OK)
            continue;
        else
            break;
    }
    return result;

}
QuestFitError_e QuestFitInstrumentDriver_fpe_send_configLut(QuestFitfpe_ct_lut_t *lut_request, char *serial)
{
    int retry = RETRY;
    QuestFitError_e result;
    while (retry--)
    {
        result = QuestFitNetworkInterface_sendFpeConfigLut(lut_request, serial);
        if(result != QFE_OK)
            continue;
        else
            break;
    }
    return result;

}
QuestFitError_e QuestFitInstrumentDriver_fpe_send_configLcCal(QuestFitfpe_lc_cal_t *lc_cal_request, char *serial)
{
    int retry = RETRY;
    QuestFitError_e result;
    while (retry--)
    {
        result = QuestFitNetworkInterface_sendFpeConfigLcCal(lc_cal_request, serial);
        if(result != QFE_OK)
            continue;
        else
            break;
    }
    return result;

}
QuestFitError_e QuestFitInstrumentDriver_fpe_send_configReordering(QuestFitfpe_reordering_t *reorder_request, char *serial)
{
    int retry = RETRY;
    QuestFitError_e result;
    while (retry--)
    {
        result = QuestFitNetworkInterface_sendFpeConfigReordering(reorder_request, serial);
        if(result != QFE_OK)
            continue;
        else
            break;
    }
    return result;

}
QuestFitError_e QuestFitInstrumentDriver_fpe_send_configPolarity(QuestFitfpe_polarity_t *polarity_request, char *serial)
{
    int retry = RETRY;
    QuestFitError_e result;
    while (retry--)
    {
        result = QuestFitNetworkInterface_sendFpeConfigPolarity(polarity_request, serial);
        if(result != QFE_OK)
            continue;
        else
            break;
    }
    return result;

}

QuestFitError_e QuestFitInstrumentDriver_fpe_send_calibration(char* path, char* serial)
{
    return QuestFitNetworkInterface_sendCalibrationFile(path, serial);
}
QuestFitError_e QuestFitInstrumentDriver_fpe_get_calibration_progress(int32_t* progress, char* serial)
{
    return QuestFitNetworkInterface_getCalibrationProgress(progress, serial);
}