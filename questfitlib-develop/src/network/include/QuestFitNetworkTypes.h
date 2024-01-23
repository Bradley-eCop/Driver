#ifndef QUESTFIT_NET_TYPES_H
#define QUESTFIT_NET_TYPES_H
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include "QuestFitError.h"
#ifdef __MINGW32__
#define WIN_PACK __attribute((gcc_struct))
#else
#define WIN_PACK
#endif
#ifdef __GNUC__
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__)) WIN_PACK
#endif

#ifdef _MSC_VER
#define PACK(__Declaration__) __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
#endif

#define QUESTFIT_PE_CMD_GET_CONFIG 7
#define QUESTFIT_PE_CMD_ENUMERATE_PLATES 9
#define QUESTFIT_PE_CMD_GET_STATUS 10

#define QUESTFIT_FPE_CMD_SOFTWARE_RESET 1
#define QUESTFIT_FPE_CMD_ZEROIZE 2
#define QUESTFIT_FPE_CMD_GET_CONFIG 4
#define QUESTFIT_FPE_CMD_SELF_TEST 6
#define QUESTFIT_FPE_CMD_CLEAR_ERROR_LOG 7
#define QUESTFIT_FPE_CMD_GET_STATUS 8
#define QUESTFIT_FPE_CMD_GET_ERROR_LOG 9

#define QUESTFIT_SERIAL_NUM_SIZE 64
#define QUESTFIT_NUM_INPUTS 4
// CONFIG SET FLAGS
#define SET_OPERATING_MODE 0x00000001
#define SET_LOCATION_NUM 0x00000002
#define SET_FPE_MODEL_NUM 0x00000004
#define SET_FPE_SERIAL_NUM 0x00000008
#define SET_TYPE_INDICATOR 0x00000010
#define SET_ELE_ORIG_X 0x00000020
#define SET_ELE_ORIG_Y 0x00000040
#define SET_ELE_ORIG_Z 0x00000080
#define SET_WIDTH 0x00000100
#define SET_LENGTH 0x00000200
#define SET_FX_CAPACITY 0x00000400
#define SET_FY_CAPACITY 0x00000800
#define SET_FZ_CAPACITY 0x00001000
#define SET_OUTPUT_FORMAT 0x00002000
#define SET_CALC_THRESHOLD 0x00004000
#define SET_GROUP_DELAY 0x00008000
#define SET_EXCITATION_VOLTAGE 0x00010000
#define SET_X_CHANNEL_GAIN 0x00020000
#define SET_Y_CHANNEL_GAIN 0x00040000
#define SET_Z_CHANNEL_GAIN 0x00080000
#define SET_RESOLUTION 0x00100000
#define SET_X_OFFSET 0x00200000
#define SET_Y_OFFSET 0x00400000
#define SET_Z_OFFSET 0x00800000
#define SET_AUTO_TARE_ENABLE 0x01000000
#define SET_VOLTAGE_RANGE 0x02000000
#define SET_FP_MODEL_NUM 0x04000000
#define SET_FP_SERIAL_NUM 0x08000000
#define SET_FP_BOARD_NAME 0x10000000
#define SET_CHANNEL_CAPACITY 0x20000000
// END CONFIG SET FLAGS

typedef enum
{
    QUESTFIT_UNKNOWN = 0,
    QUESTFIT_NOT_CONNECTED = 1,
    QUESTFIT_CONNECTED = 2
} QuestFitConnectionState_e;

typedef enum
{
    QUESTFIT_MODE_IDLE = 0,
    QUESTFIT_MODE_FREE_RUN = 1,
    QUESTFIT_MODE_GENLOCK_IN = 2,
} QuestFitMode_e;

typedef enum
{
    QUESTFIT_FPE_MODE_IDLE = 0,
    QUESTFIT_FPE_MODE_RAW_DATA = 1,
    QUESTFIT_FPE_MODE_FREE_RUN = 2,
    QUESTFIT_FPE_MODE_SIM = 3,
    QUESTFIT_FPE_MODE_SIM_MSG = 4,
    QUESTFIT_FPE_MODE_DEBUG = 5,
} QuestFitFpeOperationMode_e;

typedef PACK(struct plate_status_s
             {
                 uint8_t SamplingState;
                 uint8_t ConnectionState;
                 uint8_t FPE_SerialNumber[QUESTFIT_SERIAL_NUM_SIZE];
             }) QuestFitplate_status_t;

typedef PACK(struct tagged_sample_s
             {
                 struct timespec Timestamp;
                 uint32_t SampleNumber;
                 uint32_t Channel;
                 float Fx;
                 float Fy;
                 float Fz;
                 float Mx;
                 float My;
                 float Mz;
                 uint32_t Trigger;
             }) QuestFittagged_sample_t;

typedef PACK(struct debug_sample_s
             {
                 uint32_t PE_SequenceNumber;
                 uint32_t FPE_SequenceNumber;
                 float Fx12;
                 float Fx34;
                 float Fy14;
                 float Fy23;
                 float Fz1;
                 float Fz2;
                 float Fz3;
                 float Fz4;
                 float Fx;
                 float Fy;
                 float Fz;
                 float Mx;
                 float My;
                 float Mz;
             }) QuestFitdebug_sample_t;

typedef PACK(struct fpe_params_s
             {
                 uint8_t enabled;
                 uint8_t operating_mode;
                 char serial_number[QUESTFIT_SERIAL_NUM_SIZE];
             }) QuestFitfpe_params_t;

typedef PACK(struct pe_config_s
             {
                 uint8_t mode;
                 uint16_t sample_rate_hz;
                 uint8_t sim_enabled;
                 QuestFitfpe_params_t fpe_list[QUESTFIT_NUM_INPUTS];
             }) QuestFitpe_config_t;

typedef PACK(struct pe_command_s
             {
                 uint32_t transaction_id;
                 uint8_t command;
             }) QuestFitpe_command_t;

typedef PACK(struct pe_status_s
             {
                 uint8_t state;
                 uint16_t status;
                 uint8_t sw_version_major;
                 uint8_t sw_version_minor;
                 uint8_t sw_revision;
             }) QuestFitpe_status_t;

typedef PACK(struct fpe_enumeration_s
             {
                 uint32_t count;
                 char serial_number[QUESTFIT_NUM_INPUTS][QUESTFIT_SERIAL_NUM_SIZE];
             }) QuestFitfpe_enumeration_t;

typedef PACK(struct plate_command_s
             {
                 uint8_t enabled;
                 uint8_t operating_mode;
                 uint8_t zeroize;
             }) QuestFitplate_command_t;

typedef PACK(struct fpe_command_request_s
             {
                 uint32_t transaction_id;
                 uint8_t command;
             }) QuestFitfpe_command_request_t;

typedef PACK(struct fpe_command_response_s
             {
                 uint32_t transaction_id;
                 uint8_t acknack;
             }) QuestFitfpe_command_response_t;

typedef PACK(struct fpe_status_response_s
             {
                 uint8_t state;
                 uint16_t status;
                 uint32_t missed_samples;
                 uint8_t sw_version_major;
                 uint8_t sw_version_minor;
                 uint8_t sw_revision;
             }) QuestFitfpe_status_response_t;

typedef PACK(struct flash_config_data_s
             {
                 uint32_t StartSentinelValue;
                 // Device Info
                 uint8_t FPE_ModelNumber[64];
                 uint8_t FPE_SerialNumber[64];
                 uint8_t FP_ModelNumber[64];
                 uint8_t FP_SerialNumber[64];
                 uint8_t FP_BoardName[64];

                 // DAS Info
                 float ExcitationVoltage;
                 float VoltageRange;
                 float XChannelGain;
                 float YChannelGain;
                 float ZChannelGain;
                 uint32_t Resolution;

                 // Plate info
                 uint8_t SystemIndex;
                 uint8_t TypeIndicator;
                 float OriginX;
                 float OriginY;
                 float OriginZ;
                 float PlateXSize;
                 float PlateYSize;
                 float ChannelCapacity[6]; // Fx, Fy, Fz, Mx, My, Mz
                 uint16_t ActiveThreshold;
                 uint8_t OperatingMode;
                 uint8_t OutputFormat;
                 uint32_t GroupDelay;

                 // Sensor Info
                 float XOffset;
                 float YOffset;
                 float ZOffsetVolts;
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
                 int8_t Fx1Polarity;
                 int8_t Fy1Polarity;
                 int8_t Fz1Polarity;

                 int8_t Fx2Polarity;
                 int8_t Fy2Polarity;
                 int8_t Fz2Polarity;

                 int8_t Fx3Polarity;
                 int8_t Fy3Polarity;
                 int8_t Fz3Polarity;

                 int8_t Fx4Polarity;
                 int8_t Fy4Polarity;
                 int8_t Fz4Polarity;

                 uint8_t AutoTareEnable;
                 uint8_t ChannelOrder[12];

                 uint32_t EndSentinelValue;
             }) QuestFitfpe_config_response_t;

typedef PACK(struct flash_config_request_s
             {
                 uint32_t setParameterFlags;
                 uint8_t OperatingMode;
                 uint8_t SystemIndex;
                 // Device Info
                 uint8_t FPE_ModelNumber[64];
                 uint8_t FPE_SerialNumber[64];
                 uint8_t FP_ModelNumber[64];
                 uint8_t FP_SerialNumber[64];
                 uint8_t FP_BoardName[64];

                 uint8_t TypeIndicator;

                 // Plate info
                 float OriginX;
                 float OriginY;
                 float OriginZ;
                 float PlateXSize;
                 float PlateYSize;
                 float ChannelCapacity[6]; // Fx, Fy, Fz, Mx, My, Mz

                 float FxCapacity;
                 float FyCapacity;
                 float FzCapacity;

                 uint8_t OutputFormat;

                 uint16_t ActiveThreshold;
                 uint32_t GroupDelay;

                 // DAS Info
                 float ExcitationVoltage;
                 float VoltageRange;
                 float XChannelGain;
                 float YChannelGain;
                 float ZChannelGain;
                 uint32_t Resolution;

                 // Sensor Info
                 float XOffset;
                 float YOffset;
                 float ZOffsetVolts;
                 uint8_t AutoTareEnable;
             }) QuestFitfpe_config_request_t;

typedef PACK(struct fpe_lc_cal_s
             {
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
             }) QuestFitfpe_lc_cal_t;

typedef PACK(struct fpe_ct_lut_s
             {
                 uint8_t tableNumber;
                 // Section for CT LUTs
                 float CT_LUT_C1;
                 float CT_LUT_C2;
                 float CT_LUT_C3;
                 float CT_LUT_C4;
                 float CT_LUT_C5;
                 float CT_LUT_C6;
             }) QuestFitfpe_ct_lut_t;

typedef PACK(struct fpe_polatiry_s
             {
                 // Section for Polarity
                 int8_t Fx1Polarity;
                 int8_t Fy1Polarity;
                 int8_t Fz1Polarity;

                 int8_t Fx2Polarity;
                 int8_t Fy2Polarity;
                 int8_t Fz2Polarity;

                 int8_t Fx3Polarity;
                 int8_t Fy3Polarity;
                 int8_t Fz3Polarity;

                 int8_t Fx4Polarity;
                 int8_t Fy4Polarity;
                 int8_t Fz4Polarity;
             }) QuestFitfpe_polarity_t;

typedef PACK(struct fpe_reordering_s
             {
                 // Section for Polarity
                 uint8_t ChannelOrder[12];
             }) QuestFitfpe_reordering_t;

extern int process_int(int var);
extern QuestFitError_e QuestFitNetwork_Process_PE_Config_Message(char *buf, uint32_t len, QuestFitpe_config_t *status);
extern QuestFitError_e QuestFitNetwork_Process_PE_Status_Message(char *buf, uint32_t len, QuestFitpe_status_t *status);
extern QuestFitError_e QuestFitNetwork_Process_FPE_Enumeration_Message(char *buf, uint32_t len, QuestFitfpe_enumeration_t *enumeration);
extern QuestFitError_e QuestFitNetwork_Process_FPE_Status_Message(char *buf, uint32_t len, QuestFitfpe_status_response_t *status);
extern QuestFitError_e QuestFitNetwork_Process_FPE_Config_Message(char *buf, uint32_t len, QuestFitfpe_config_response_t *config);
extern QuestFitError_e QuestFitNetwork_Process_FPE_debug_Data_Message(char *buf, uint32_t len, QuestFitdebug_sample_t *sample);

#endif //QUESTFIT_NET_TYPES_H