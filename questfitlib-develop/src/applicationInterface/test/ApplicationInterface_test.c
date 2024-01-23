#include "QuestFitApplicationInterface.h"
#include <windows.h>
int main(void){
    QuestFitError_e  result;
    QuestFitApplicationInterface_fpe_enumeration_t enumeration;
    QuestFitApplicationInterface_Initialize();
    Sleep(2000);
    result = QuestFitApplicationInterface_GetFPEEnumeration(&enumeration);
    if (result != QFE_OK)
        return result;
    QuestFitApplicationInterface_fpe_daq_t fpeDaq;
    QuestFitApplicationInterface_fpe_status_t fpeStatus;
    result = QuestFitApplicationInterface_GetFPEDAQ(&fpeDaq, enumeration.serial_number[0]);
    if (result != QFE_OK)
        return result;
    printf("X Gain %f\n", fpeDaq.xChannelGain);
    for(int i=0; i<4; i++)
    {
        fpeDaq.xChannelGain = i;
        fpeDaq.yChannelGain = i;
        fpeDaq.zChannelGain = i;

        result = QuestFitApplicationInterface_SetFPEDAQ(&fpeDaq, enumeration.serial_number[0]);
        if (result != QFE_OK)
            return result;
        result = QuestFitApplicationInterface_GetFPEStatus(&fpeStatus, enumeration.serial_number[0]);
        if (result != QFE_OK)
            return result;
        result = QuestFitApplicationInterface_GetFPEDAQ(&fpeDaq, enumeration.serial_number[0]);
        if (result != QFE_OK)
            return result;
        printf("X Gain %f expected %d\n", fpeDaq.xChannelGain, i);
    }


    return 0;
}