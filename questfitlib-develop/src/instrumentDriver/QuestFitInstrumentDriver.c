#include "QuestFitInstrumentDriver.h"
#include "QuestFitNetworkInterface.h"


QuestFitError_e QuestFitInstrumentDriver_Initialize()
{
    // Initialize Network interface
    QuestFitNetworkInterface_Initialize();

    return QFE_OK;
}