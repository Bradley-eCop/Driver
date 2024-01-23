#include <stdlib.h>
#include <string.h>
#include "QuestFitCircularBuffer.h"
#include "QuestFitCommon.h"
struct QuestFitCircularBuffer_t {
    uint8_t* buffer_start;
    uint8_t* buffer_end;
    uint8_t* head;
    uint8_t* tail;
    size_t size;
    size_t data_size;
};
__declspec(dllexport) QuestFitError_e QuestFitCircularBuffer_init(size_t count, size_t data_size, qfcircular_buf_handle_t* handle)
{
    // Allocate handle structure
    *handle = malloc(sizeof(QuestFitCircularBuffer_t)); 
    QuestFitCircularBuffer_t* internalHandle = *handle;

    // Allocate buffer
    internalHandle->buffer_start = (uint8_t*)malloc(count * data_size);
    internalHandle->buffer_end = (internalHandle->buffer_start) + (count * data_size);
    internalHandle->head = internalHandle->buffer_start;
    internalHandle->tail = internalHandle->buffer_start;
    internalHandle->size = count;
    internalHandle->data_size = data_size;

}
__declspec(dllexport) QuestFitError_e QuestFitCircularBuffer_free(qfcircular_buf_handle_t handle)
{
    // Free the buffer
    free(handle->buffer_start);
    elogDebug("Freed buffer");
    free(handle);
    elogDebug("Freed struct");
}
__declspec(dllexport) QuestFitError_e QuestFitCircularBuffer_reset(qfcircular_buf_handle_t handle)
{
    handle->head = handle->buffer_start;
    handle->tail = handle->buffer_start;
}
__declspec(dllexport) QuestFitError_e QuestFitCircularBuffer_put(qfcircular_buf_handle_t handle, void* data)
{
    if(handle == NULL)
    {
        return QFE_NOT_CONNECTED;
    }
    memcpy_s(handle->head, handle->data_size, data, handle->data_size);
    // Advance head
    handle->head += handle->data_size;
    if(handle->head >= handle->buffer_end)
    {
        // Move the head back to the start of the buffer
        handle->head = handle->buffer_start;
    }
    // Check for full status and 
    if(handle->head == handle->tail)
    {
        elogDebug("Pushing tail back");
        // Advance the tail forward one block
        handle->tail += handle->data_size;
        if(handle->tail >= handle->buffer_end)
        {
            elogDebug("Wrapping tail to start");
            // Move the tail back to the start of the buffer
            handle->tail = handle->buffer_start;
        }
    }
}
__declspec(dllexport) QuestFitError_e QuestFitCircularBuffer_get(qfcircular_buf_handle_t handle, uint8_t* data, size_t count, size_t* data_retrieved)
{
    // Determine number of bytes to copy
    if(handle == NULL)
    {
        return QFE_NOT_CONNECTED;
    }
    size_t numberOfBytes = count * handle->data_size;
    *data_retrieved = 0;
    elogDebug("Number of Bytes: %d", numberOfBytes);

    while(numberOfBytes)
    {
        // Check to see if there is no more available data
        if(handle->head == handle->tail)
        {
            elogDebug("Tail has caught up to head");
            break;
        }
        // Determine available data
        size_t bytesAvailable = 0;
        // If the buffer end is between the tail and the head
        if(handle->tail > handle->head)
        {
            bytesAvailable = handle->buffer_end - handle->tail;
        }
        // The tail value is less than the head value
        else
        {
            bytesAvailable = handle->head - handle->tail;
        }
        elogDebug("Bytes available: %d", bytesAvailable);
        if (bytesAvailable >= handle->data_size)
        {
            size_t bytesRead = min(bytesAvailable, numberOfBytes);
            memcpy_s(data, bytesRead, handle->tail, bytesRead);
            data += bytesRead; // Increment data pointer
            // Advance tail by number of bytes read
            handle->tail += bytesRead;
            numberOfBytes -= bytesRead;
            *data_retrieved += bytesRead / handle->data_size;

            if(handle->tail >= handle->buffer_end)
            {
                // Move the tail back to the start of the buffer
                handle->tail = handle->buffer_start;
            }
        }
        else
        {
            elogDebug("not enough data");
            break;
        }
    }
}
__declspec(dllexport) QuestFitError_e QuestFitCircularBuffer_getAvailable(qfcircular_buf_handle_t handle, size_t count, size_t* data_retrieved)
{
    // Determine number of bytes to copy
    size_t numberOfBytes = count * handle->data_size;
    *data_retrieved = 0;
    
    // Copy the buffer structure to peek
    uint8_t* buffer_start = handle->buffer_start;
    uint8_t* buffer_end = handle->buffer_end;
    uint8_t* head = handle->head;
    uint8_t* tail = handle->tail;
    size_t size = handle->size;
    size_t data_size = handle->data_size;

    while(numberOfBytes)
    {
        // Check to see if there is no more available data
        if(head == tail)
        {
            break;
        }
        // Determine available data
        size_t bytesAvailable = 0;
        // If the buffer end is between the tail and the head
        if(tail > head)
        {
            bytesAvailable = buffer_end - tail;
        }
        // The tail value is less than the head value
        else
        {
            bytesAvailable = head - tail;
        }
        if (bytesAvailable >= data_size)
        {
            size_t bytesRead = min(bytesAvailable, numberOfBytes);
            // Advance tail by number of bytes read
            tail += bytesRead;
            numberOfBytes -= bytesRead;
            *data_retrieved += bytesRead / data_size;

            if(tail >= buffer_end)
            {
                // Move the tail back to the start of the buffer
                tail = buffer_start;
            }
        }
        else
        {
            break;
        }
    }
}