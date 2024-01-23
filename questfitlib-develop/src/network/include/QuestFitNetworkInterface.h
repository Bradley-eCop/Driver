#include "QuestFitCommon.h"
#include "QuestFitNetworkTypes.h"
extern QuestFitError_e QuestFitNetworkInterface_sendPeConfig(QuestFitpe_config_t *config);
extern QuestFitError_e QuestFitNetworkInterface_setPeConfig(QuestFitpe_config_t *config);
extern QuestFitError_e QuestFitNetworkInterface_getPeConfig(QuestFitpe_config_t *config, bool blockForUpdate);
extern QuestFitError_e QuestFitNetworkInterface_initializePeConfig(QuestFitpe_config_t *config);
extern QuestFitError_e QuestFitNetworkInterface_setPeStatus(QuestFitpe_status_t *status);
extern QuestFitError_e QuestFitNetworkInterface_getPeStatus(QuestFitpe_status_t *status, bool blockForUpdate);
extern QuestFitError_e QuestFitNetworkInterface_setFpeEnumeration(QuestFitfpe_enumeration_t *enumeration);
extern QuestFitError_e QuestFitNetworkInterface_getFpeEnumeration(QuestFitfpe_enumeration_t *enumeration, bool blockForUpdate);
extern QuestFitError_e QuestFitNetworkInterface_setFpeStatus(QuestFitfpe_status_response_t *status, char *serial);
extern QuestFitError_e QuestFitNetworkInterface_getFpeStatus(QuestFitfpe_status_response_t *status, char *serial, bool blockForUpdate);
extern QuestFitError_e QuestFitNetworkInterface_setFpeConfig(QuestFitfpe_config_response_t *config, char *serial);
extern QuestFitError_e QuestFitNetworkInterface_getFpeConfig(QuestFitfpe_config_response_t *config, char *serialNumber, bool blockForUpdate);
extern QuestFitError_e QuestFitNetworkInterface_sendFpeConfig(QuestFitfpe_config_response_t *config, char *serialNumber);
extern QuestFitError_e QuestFitNetworkInterface_sendFpeConfigOnly(QuestFitfpe_config_request_t *config, char *serialNumber);
extern QuestFitError_e QuestFitNetworkInterface_sendFpeConfigLut(QuestFitfpe_ct_lut_t *lut_request, char *serialNumber);
extern QuestFitError_e QuestFitNetworkInterface_sendFpeConfigLcCal(QuestFitfpe_lc_cal_t *lc_cal_request, char *serialNumber);
extern QuestFitError_e QuestFitNetworkInterface_sendFpeConfigReordering(QuestFitfpe_reordering_t *reorder_request, char *serialNumber);
extern QuestFitError_e QuestFitNetworkInterface_sendFpeConfigPolarity(QuestFitfpe_polarity_t *polarity_request, char *serialNumber);
extern QuestFitError_e QuestFitNetworkInterface_storeDebugSample(QuestFitdebug_sample_t *sample, char *serial);
extern QuestFitError_e QuestFitNetworkInterface_clearDebugSamples();
extern QuestFitError_e QuestFitNetworkInterface_getDebugSamples(QuestFitdebug_sample_t *samples, char *serialNumber, size_t maxSampleCount, size_t *data_retrieved, bool waitForFull);
extern QuestFitError_e QuestFitNetworkInterface_setCalibrationProgress(int32_t progress, char *serial);
extern QuestFitError_e QuestFitNetworkInterface_getCalibrationProgress(int32_t *progress, char *serial);
extern QuestFitError_e QuestFitNetworkInterface_startDebugMode(char *serialNumber);
extern QuestFitError_e QuestFitNetworkInterface_stopDebugMode(char *serialNumber);
extern QuestFitError_e QuestFitNetworkInterface_setTestNumber(int number);
extern QuestFitError_e QuestFitNetworkInterface_getTestNumber(int *number, bool blockForUpdate);
extern QuestFitError_e QuestFitNetworkInterface_sendPlatformUpdate(char *path);
extern QuestFitError_e QuestFitNetworkInterface_sendCalibrationFile(char *path, char *serial);

extern QuestFitError_e QuestFitNetworkInterface_Initialize();
extern QuestFitError_e QuestFitNetworkInterface_Destroy();
