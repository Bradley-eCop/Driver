
#include <stdint.h>
#include "QuestFitCommon.h"

typedef struct QuestFitCircularBuffer_t QuestFitCircularBuffer_t;
typedef QuestFitCircularBuffer_t* qfcircular_buf_handle_t;

__declspec(dllexport) extern QuestFitError_e QuestFitCircularBuffer_init(size_t count, size_t data_size, qfcircular_buf_handle_t* handle);
__declspec(dllexport) extern QuestFitError_e QuestFitCircularBuffer_free(qfcircular_buf_handle_t handle);
__declspec(dllexport) extern QuestFitError_e QuestFitCircularBuffer_reset(qfcircular_buf_handle_t handle);
__declspec(dllexport) extern QuestFitError_e QuestFitCircularBuffer_put(qfcircular_buf_handle_t handle, void* data);
__declspec(dllexport) extern QuestFitError_e QuestFitCircularBuffer_get(qfcircular_buf_handle_t handle, uint8_t* data, size_t count, size_t* data_retrieved);
__declspec(dllexport) extern QuestFitError_e QuestFitCircularBuffer_getAvailable(qfcircular_buf_handle_t handle, size_t count, size_t* data_retrieved);


