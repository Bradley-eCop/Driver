#ifndef QUESTFIT_APPLICATION_INTERFACE_H
#define QUESTFIT_APPLICATION_INTERFACE_H
#include <stdint.h>
#include "QuestFitNetworkTypes.h"
typedef struct
{
    uint8_t state;
    uint16_t status;
    uint8_t sw_version_major;
    uint8_t sw_version_minor;
    uint8_t sw_revision;
} QuestFitApplicationInterface_pe_status_t;

typedef struct
{
    uint32_t count;
    char serial_number[QUESTFIT_NUM_INPUTS][QUESTFIT_SERIAL_NUM_SIZE];
} QuestFitApplicationInterface_fpe_enumeration_t;
typedef struct
{
    uint8_t state;
    uint16_t status;
    uint32_t missed_samples;
    uint8_t sw_version_major;
    uint8_t sw_version_minor;
    uint8_t sw_revision;
} QuestFitApplicationInterface_fpe_status_t;

typedef struct
{
    char fpeModelNumber[64];
    char fpeSerialNumber[64];
    char fpModelNumber[64];
    char fpSerialNumber[64];
    char firmwareRevision[64];
    char fpBoardName[64];
} QuestFitApplicationInterface_fpe_info_t;
typedef struct
{
    float excitationVoltage;
    float voltageRange;
    float xChannelGain;
    float yChannelGain;
    float zChannelGain;
    float zOffsetVolts;
    uint32_t resolution;
    uint32_t sampleRate;
} QuestFitApplicationInterface_fpe_daq_t;

typedef struct
{
    uint8_t Index;
    uint8_t Type;
    float Origin[3];
    float Offset[2];
    float Size[2];
    float ChannelCapacity[6];
    uint16_t ActiveThreshold;
    float TaredValues[6];
    uint8_t OperatingMode;
    uint8_t OutputFormat;
    uint32_t GroupDelay;
} QuestFitApplicationInterface_fpe_plate_t;

typedef struct
{
    float FxCapacity;
    float FyCapacity;
    float FzCapacity;
    // LC Cal values
    float Fx1mvPerVolt;
    float Fy1mvPerVolt;
    float Fz1mvPerVolt;

    float Fx2mvPerVolt;
    float Fy2mvPerVolt;
    float Fz2mvPerVolt;

    float Fx3mvPerVolt;
    float Fy3mvPerVolt;
    float Fz3mvPerVolt;

    float Fx4mvPerVolt;
    float Fy4mvPerVolt;
    float Fz4mvPerVolt;

    // Section for CT LUTs
    float Fx1CTalkOnFy1;
    float Fx1CTalkOnFz1;
    float Fy1CTalkOnFx1;
    float Fy1CTalkOnFz1;
    float Fz1CTalkOnFx1;
    float Fz1CTalkOnFy1;

    float Fx2CTalkOnFy2;
    float Fx2CTalkOnFz2;
    float Fy2CTalkOnFx2;
    float Fy2CTalkOnFz2;
    float Fz2CTalkOnFx2;
    float Fz2CTalkOnFy2;

    float Fx3CTalkOnFy3;
    float Fx3CTalkOnFz3;
    float Fy3CTalkOnFx3;
    float Fy3CTalkOnFz3;
    float Fz3CTalkOnFx3;
    float Fz3CTalkOnFy3;

    float Fx4CTalkOnFy4;
    float Fx4CTalkOnFz4;
    float Fy4CTalkOnFx4;
    float Fy4CTalkOnFz4;
    float Fz4CTalkOnFx4;
    float Fz4CTalkOnFy4;

    // Section for Polarity
    int8_t ChannelPolarity[12];
    bool AutoTareEnable;
    uint8_t ChannelOrder[12];
} QuestFitApplicationInterface_fpe_sensor_t;

typedef struct
{
    char ModelNumber[64];
    char SerialNumber[64];
    char FirmwareRevision[64];
    uint64_t FirmwareDate; // Unix time
} QuestFitApplicationInterface_platform_info_t;

/**
 * @brief Get the platform status
 * 
 * This funciton returns the current platform status
 * @param enumeration pointer to a QuestFitApplicationInterface_pe_status_t structure to be populated
 * <b>Example Code</b> 
 * @code
 *   QuestFitApplicationInterface_pe_status_t status;
 *   QuestFitError_e result =  QuestFitApplicationInterface_GetPeStatus(&status);
 * @endcode
 */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_GetPeStatus(QuestFitApplicationInterface_pe_status_t *status);
/**
 * @brief Enumerates the available FPEs
 * 
 * This funciton returns all available FPEs in the platform
 * @param enumeration pointer to a QuestFitApplicationInterface_fpe_enumeration_t structure to be populated
 * <b>Example Code</b> 
 * @code
 *   QuestFitApplicationInterface_fpe_enumeration_t enumeration;
 *   QuestFitError_e result =  QuestFitApplicationInterface_GetFpeEnumeration(&enumeration);
 * @endcode
 */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_GetFPEEnumeration(QuestFitApplicationInterface_fpe_enumeration_t *enumeration);
/**
 * @brief Gets the status of an FPE
 * 
 * This funciton returns the status of a given FPE
 * @param status pointer to a QuestFitApplicationInterface_fpe_status_t structure to be populated
 * @param serial String serial number of the FPE
 * <b>Example Code</b> 
 * @code
 *   QuestFitApplicationInterface_fpe_status_t status;
 *   char serial[64] = "00015";
 *   QuestFitError_e result =  QuestFitApplicationInterface_GetFPEStatus(&status, serial);
 * @endcode
 */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_GetFPEStatus(QuestFitApplicationInterface_fpe_status_t *status, char *serial);
/**
 * @brief Initializes the platform
 * 
 * This funciton takes care of initializing the platform and connecting to the Quest Fit hardware
 * <b>Example Code</b> 
 * @code
 *   QuestFitError_e result =  QuestFitApplicationInterface_Initialize();
 * @endcode
 */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_Initialize();

/**
 * @brief Deinitializes the platform
 * 
 * This funciton takes care of closing any connections and freeing any memory used by the platform
 * <b>Example Code</b> 
 * @code
 *   QuestFitError_e result =  QuestFitApplicationInterface_Destroy();
 * @endcode
 */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_Destroy();

// FPE Command Section

// PE Command Section
/**
 * @brief Sets the index order of the FPEs
 * @param serialNumberList - A comma separated list of FPE serial numbers in order according to their desired index
 * 
 * <b>Example Code</b> 
 * @code
 *   char serialNumberList[100] = "0011,0022,0044,0033";
 *   QuestFitError_e result =  QuestFitApplicationInterface_SetFPEOrder(serialNumberList);
 * @endcode
 */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_SetFPEOrder(char *serialNumberList);
/**
 * @brief Starts the Auto-order process for the FPES
 * 
 * <b>Example Code</b> 
 * @code
 *   QuestFitError_e result =  QuestFitApplicationInterface_StartAutoOrder();
 * @endcode
 */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_StartFPEAutoOrder();
/**
 * @brief Stops the Auto-order process for the FPES
 * 
 * <b>Example Code</b> 
 * @code
 *   QuestFitError_e result =  QuestFitApplicationInterface_StopAutoOrder();
 * @endcode
 */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_StopFPEAutoOrder();

/**
 * @brief Sends an update package to the platform
 * This function enables the update capability of the QuesstFit platform. By providing a file path as
 * the parameter, the caller initiates the download process to the Platform Electronics and all associated
 * Force Plates
 * @param path String path that corresponds to the location of the update file
 * 
 * <b>Example Code</b> 
 * @code
 *   char filePath[100] = "C:\Platform\QuestFit2.0.swu";
 *   QuestFitError_e result =  QuestFitApplicationInterface_SendPlatformUpdate(filePath);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_SendPlatformUpdate(char *path);

/**
 * @brief Sends a calibration package to an FPE
 * This function enables the calibration upload capability of a QuesstFit FPE. By providing a file path as
 * the parameter, the caller initiates the download process to the Force Plate
 * @param path String path that corresponds to the location of the calibration file
 * @param serialNumber String serial number of the FPE
 * 
 * <b>Example Code</b> 
 * @code
 *   char filePath[100]  = "C:\FPE\QF00015_20210820.zip";
 *   char serialNumber[100]  = "00015";
 *   QuestFitError_e result =  QuestFitApplicationInterface_SendCalibrationFile(filePath, serialNumber);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_SendCalibrationFile(char *path, char *serialNumber);

/**
 * @brief Gets the current calibration upload progress
 * This function provides the current progress level (0-100) of the calibration file upload
 * @param progress [out] Pointer to an integer, the current upload progress
 * @param serialNumber String serial number of the FPE
 * 
 * <b>Example Code</b> 
 * @code
 *   int32_t progress = 0;
 *   char serialNumber[100]  = "00015";
 * 
 *   QuestFitError_e result =  QuestFitApplicationInterface_GetCalibrationProgress(&progress, serialNumber);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_GetCalibrationProgress(int32_t *progress, char *serial);

/**
 * @brief Gets FPE Info
 * This function returns the FPE information for a single FPE
 * @param fpeInfo pointer to fpe info structure
 * @param serialNumber String serial number of the FPE
 * 
 * <b>Example Code</b> 
 * @code
 *   int index = 1;
 *   QuestFitApplicationInterface_fpe_info_t fpeInfo;
 *   QuestFitError_e result =  QuestFitApplicationInterface_GetFPEInfo(index, &fpeInfo);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_GetFPEInfo(QuestFitApplicationInterface_fpe_info_t *fpeInfo, char* serial);

/**
 * @brief Gets FPE DAQ Info
 * This function returns the FPE DAQ information for a single FPE
 * @param fpeInfo pointer to fpe DAQ structure
 * @param serialNumber String serial number of the FPE
 * 
 * <b>Example Code</b> 
 * @code
 *   int index = 1;
 *   QuestFitApplicationInterface_fpe_daq_t fpeDaq;
 *   QuestFitError_e result =  QuestFitApplicationInterface_GetFPEDAQ(index, &fpeDaq);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_GetFPEDAQ(QuestFitApplicationInterface_fpe_daq_t *fpeDaq, char* serial);

/**
 * @brief Gets FPE Plate Info
 * This function returns the FPE Plate information for a single FPE
 * @param fpeInfo pointer to fpe Plate structure
 * @param serialNumber String serial number of the FPE
 * 
 * <b>Example Code</b> 
 * @code
 *   int index = 1;
 *   QuestFitApplicationInterface_fpe_plate_t fpePlate;
 *   QuestFitError_e result =  QuestFitApplicationInterface_GetFPEPlate(index, &fpePlate);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_GetFPEPlate(QuestFitApplicationInterface_fpe_plate_t *fpePlate, char* serial);

/**
 * @brief Gets FPE Sensor Info
 * This function returns the FPE Sensor information for a single FPE
 * @param fpeInfo pointer to fpe Sensor structure
 * @param serialNumber String serial number of the FPE
 * 
 * <b>Example Code</b> 
 * @code
 *   int index = 1;
 *   QuestFitApplicationInterface_fpe_sensor_t fpeSensor;
 *   QuestFitError_e result =  QuestFitApplicationInterface_GetFPESensor(index, &fpeSensor);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_GetFPESensor(QuestFitApplicationInterface_fpe_sensor_t *fpeSensor, char* serial);

/**
 * @brief Sets FPE Info
 * This function returns the FPE information for a single FPE
 * @param fpeInfo pointer to fpe info structure
 * @param serialNumber String serial number of the FPE
 * 
 * <b>Example Code</b> 
 * @code
 *   int index = 1;
 *   QuestFitApplicationInterface_fpe_info_t fpeInfo;
 *   QuestFitError_e result =  QuestFitApplicationInterface_SetFPEInfo(index, &fpeInfo);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_SetFPEInfo(QuestFitApplicationInterface_fpe_info_t *fpeInfo, char* serial);

/**
 * @brief Sets FPE DAQ Info
 * This function returns the FPE DAQ information for a single FPE
 * @param fpeInfo pointer to fpe DAQ structure
 * @param serialNumber String serial number of the FPE
 * 
 * <b>Example Code</b> 
 * @code
 *   int index = 1;
 *   QuestFitApplicationInterface_fpe_daq_t fpeDaq;
 *   QuestFitError_e result =  QuestFitApplicationInterface_SetFPEDAQ(index, &fpeDaq);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_SetFPEDAQ(QuestFitApplicationInterface_fpe_daq_t *fpeDaq, char* serial);

/**
 * @brief Sets FPE Plate Info
 * This function returns the FPE Plate information for a single FPE
 * @param fpeInfo pointer to fpe Plate structure
 * @param serialNumber String serial number of the FPE
 * 
 * <b>Example Code</b> 
 * @code
 *   int index = 1;
 *   QuestFitApplicationInterface_fpe_plate_t fpePlate;
 *   QuestFitError_e result =  QuestFitApplicationInterface_SetFPEPlate(index, &fpePlate);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_SetFPEPlate(QuestFitApplicationInterface_fpe_plate_t *fpePlate, char* serial);

/**
 * @brief Sets FPE Sensor Info
 * This function returns the FPE Sensor information for a single FPE
 * @param fpeInfo pointer to fpe Sensor structure
 * @param serialNumber String serial number of the FPE
 * 
 * <b>Example Code</b> 
 * @code
 *   int index = 1;
 *   QuestFitApplicationInterface_fpe_sensor_t fpeSensor;
 *   QuestFitError_e result =  QuestFitApplicationInterface_SetFPESensor(index, &fpeSensor);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_SetFPESensor(QuestFitApplicationInterface_fpe_sensor_t *fpeSensor, char* serial);

/**
 * @brief Gets Platform Info
 * This function returns the Platform information
 * @param platformInfo pointer to platform info structure
 * 
 * <b>Example Code</b> 
 * @code
 *   int index = 1;
 *   QuestFitApplicationInterface_platform_info_t platformInfo;
 *   QuestFitError_e result =  QuestFitApplicationInterface_GetPlatformInfo(&platformInfo);
 * @endcode
 * */
__declspec(dllexport) extern QuestFitError_e QuestFitApplicationInterface_GetPlatformInfo(QuestFitApplicationInterface_platform_info_t *platformInfo);
#endif // QUESTFIT_APPLICATION_INTERFACE_H
