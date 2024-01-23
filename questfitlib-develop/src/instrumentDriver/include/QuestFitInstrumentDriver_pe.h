#ifndef QUESTFIT_INSTRUMENT_DRIVER_PE_H
#define QUESTFIT_INSTRUMENT_DRIVER_PE_H

#include "QuestFitInstrumentDriver.h"
#include "QuestFitNetworkTypes.h"

extern QuestFitError_e QuestFitInstrumentDriver_pe_get_status(QuestFitpe_status_t *status);
/**
 * @brief Sends an update package to the platform
 * This function enables the update capability of the QuesstFit platform. By providing a file path as
 * the parameter, the caller initiates the download process to the Platform Electronics and all associated
 * Force Plates
 * @param path String path that corresponds to the location of the update file
 */
extern QuestFitError_e QuestFitInstrumentDriver_pe_send_update(char *path);
extern QuestFitError_e QuestFitInstrumentDriver_pe_get_config(QuestFitpe_config_t *config);
#endif //QUESTFIT_INSTRUMENT_DRIVER_PE_H
