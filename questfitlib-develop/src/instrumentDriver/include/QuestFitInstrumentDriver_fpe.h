#ifndef QUESTFIT_INSTRUMENT_DRIVER_FPE_H
#define QUESTFIT_INSTRUMENT_DRIVER_FPE_H

#include "QuestFitInstrumentDriver.h"
#include "QuestFitNetworkTypes.h"

extern QuestFitError_e QuestFitInstrumentDriver_fpe_get_enumeration(QuestFitfpe_enumeration_t *enumeration);
extern QuestFitError_e QuestFitInstrumentDriver_fpe_get_status(QuestFitfpe_status_response_t *status, char* serial);
extern QuestFitError_e QuestFitInstrumentDriver_fpe_get_configuration(QuestFitfpe_config_response_t *config, char* serial);
extern QuestFitError_e QuestFitInstrumentDriver_fpe_send_configuration(QuestFitfpe_config_response_t *config, char* serial);
extern QuestFitError_e QuestFitInstrumentDriver_fpe_send_ConfigOnly(QuestFitfpe_config_request_t *config, char *serial);
extern QuestFitError_e QuestFitInstrumentDriver_fpe_send_configLut(QuestFitfpe_ct_lut_t *lut_request, char *serial);
extern QuestFitError_e QuestFitInstrumentDriver_fpe_send_configLcCal(QuestFitfpe_lc_cal_t *lc_cal_request, char *serial);
extern QuestFitError_e QuestFitInstrumentDriver_fpe_send_configReordering(QuestFitfpe_reordering_t *reorder_request, char *serial);
extern QuestFitError_e QuestFitInstrumentDriver_fpe_send_configPolarity(QuestFitfpe_polarity_t *polarity_request, char *serial);
extern QuestFitError_e QuestFitInstrumentDriver_fpe_send_calibration(char* path, char* serial);
extern QuestFitError_e QuestFitInstrumentDriver_fpe_get_calibration_progress(int32_t* progress, char* serial);
#endif //QUESTFIT_INSTRUMENT_DRIVER_FPE_H
