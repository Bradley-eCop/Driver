#include <stdbool.h>
#include "QuestFitInstrumentDriver_pe.h"
#include "QuestFitNetworkInterface.h"

#define RETRY 5
QuestFitError_e QuestFitInstrumentDriver_pe_get_status(QuestFitpe_status_t *status)
{
    int retry = RETRY;
    QuestFitError_e result;
    while (retry--)
    {
        result= QuestFitNetworkInterface_getPeStatus(status, true);
        if(result != QFE_OK)
            continue;
        else
            break;
    }
    return result;
}

QuestFitError_e QuestFitInstrumentDriver_pe_get_config(QuestFitpe_config_t *config)
{
    int retry = RETRY;
    QuestFitError_e result;
    while (retry--)
    {
        result =  QuestFitNetworkInterface_getPeConfig(config, true);
        if(result != QFE_OK)
            continue;
        else
            break;
    }
    return result;
}
QuestFitError_e QuestFitInstrumentDriver_pe_send_update(char *path)
{
    return QuestFitNetworkInterface_sendPlatformUpdate(path);
}
