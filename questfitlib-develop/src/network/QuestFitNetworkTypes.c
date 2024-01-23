#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "QuestFitCommon.h"
#include "QuestFitNetworkTypes.h"

int process_int(int var)
{
    return var;
}

/**
 * Process a config message
 */
QuestFitError_e QuestFitNetwork_Process_PE_Config_Message(char *buf, uint32_t len, QuestFitpe_config_t *config)
{
    int i = 0;
    // Ensure buffer is long enough to contain pe status message
    if (len < sizeof(QuestFitpe_config_t))
    {
        elogError("Got size %d expected %d", len, sizeof(QuestFitpe_config_t));
        return QFE_INVALID_LEN;
    }
    memcpy(config, buf, sizeof(QuestFitpe_config_t));

    // Perform Data Sanity Checks
    for (i = 0; i < QUESTFIT_NUM_INPUTS; i++)
    {
        (config)->fpe_list[i].serial_number[sizeof((config)->fpe_list[i].serial_number) - 1] = NULL; // Make sure serial is terminated
    }
    return QFE_OK;
}

/**
 * Process a status message
 */
QuestFitError_e QuestFitNetwork_Process_PE_Status_Message(char *buf, uint32_t len, QuestFitpe_status_t *status)
{
    // Ensure buffer is long enough to contain pe status message
    if (len < sizeof(QuestFitpe_status_t))
    {
        elogError("Got size %d expected %d", len, sizeof(QuestFitpe_status_t));
        return QFE_INVALID_LEN;
    }
    memcpy(status, buf, sizeof(QuestFitpe_status_t));

    return QFE_OK;
}

/**
 * Process an enumeration message
 */
QuestFitError_e QuestFitNetwork_Process_FPE_Enumeration_Message(char *buf, uint32_t len, QuestFitfpe_enumeration_t *enumeration)
{
    int i = 0;
    // Ensure buffer is long enough to contain pe status message
    if (len < sizeof(QuestFitfpe_enumeration_t))
    {
        elogError("Got size %d expected %d", len, sizeof(QuestFitfpe_enumeration_t));
        return QFE_INVALID_LEN;
    }
    memcpy(enumeration, buf, sizeof(QuestFitfpe_enumeration_t));
    for (i = 0; i < QUESTFIT_NUM_INPUTS; i++)
    {
        (enumeration)->serial_number[i][sizeof((enumeration)->serial_number[i]) - 1] = NULL; // Make sure serial is terminated
    }

    return QFE_OK;
}

/**
 * Process an FPE status message
 */
QuestFitError_e QuestFitNetwork_Process_FPE_Status_Message(char *buf, uint32_t len, QuestFitfpe_status_response_t *status)
{
    // Ensure buffer is long enough to contain pe status message
    if (len < sizeof(QuestFitfpe_status_response_t))
    {
        elogError("Got size %d expected %d", len, sizeof(QuestFitfpe_status_response_t));
        return QFE_INVALID_LEN;
    }
    memcpy(status, buf, sizeof(QuestFitfpe_status_response_t));

    return QFE_OK;
}
/**
 * Process an FPE config message
 */
QuestFitError_e QuestFitNetwork_Process_FPE_Config_Message(char *buf, uint32_t len, QuestFitfpe_config_response_t *config)
{
    // Ensure buffer is long enough to contain pe status message
    if (len < sizeof(QuestFitfpe_config_response_t))
    {
        elogError("Got size %d expected %d", len, sizeof(QuestFitfpe_config_response_t));
        return QFE_INVALID_LEN;
    }
    memcpy(config, buf, sizeof(QuestFitfpe_config_response_t));

    return QFE_OK;
}
/**
 * Process an FPE debug data message
 */
QuestFitError_e QuestFitNetwork_Process_FPE_debug_Data_Message(char *buf, uint32_t len, QuestFitdebug_sample_t *sample)
{
    // Ensure buffer is long enough to contain pe status message
    if (len < sizeof(QuestFitdebug_sample_t))
    {
        elogError("Got size %d expected %d", len, sizeof(QuestFitdebug_sample_t));
        return QFE_INVALID_LEN;
    }
    memcpy(sample, buf, sizeof(QuestFitdebug_sample_t));

    return QFE_OK;
}