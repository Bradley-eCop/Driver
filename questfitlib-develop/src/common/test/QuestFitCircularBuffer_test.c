
#include "QuestfitCommon.h"
#include "QuestFitCircularBuffer.h"

int main(void)
{
    int i=0;
    uint8_t data_out[10];
    uint32_t data_out_2[10];
    size_t count_retrieved;
    qfcircular_buf_handle_t circular_buffer;
    setLogLvl(eLogLvlDebug);
    elogInfo("Starting common test");

    QuestFitCircularBuffer_init(10, sizeof(uint8_t), &circular_buffer);
    for(i=0; i<8; i++)
    {
        uint8_t data = i;
        QuestFitCircularBuffer_put(circular_buffer, &data);
    }
    QuestFitCircularBuffer_get(circular_buffer, data_out, sizeof(data_out), &count_retrieved);
    elogInfo("Count Retr: %d", count_retrieved);

    for(i=0; i<8; i++)
    {
        uint8_t data = i;
        QuestFitCircularBuffer_put(circular_buffer, &data);
    }
    QuestFitCircularBuffer_get(circular_buffer, data_out, sizeof(data_out), &count_retrieved);
    elogInfo("Count Retr: %d", count_retrieved);

    for(i=0; i<18; i++)
    {
        uint8_t data = i;
        QuestFitCircularBuffer_put(circular_buffer, &data);
    }
    QuestFitCircularBuffer_get(circular_buffer, data_out, sizeof(data_out), &count_retrieved);
    elogInfo("Count Retr: %d", count_retrieved);
    elogInfo("Freeing buffer");
    QuestFitCircularBuffer_free(circular_buffer);


    qfcircular_buf_handle_t circular_buffer2;
    setLogLvl(eLogLvlDebug);
    elogInfo("Starting common test");

    QuestFitCircularBuffer_init(10, sizeof(uint32_t), &circular_buffer2);
    for(i=0; i<8; i++)
    {
        uint32_t data = i;
        QuestFitCircularBuffer_put(circular_buffer2, &data);
    }
    QuestFitCircularBuffer_get(circular_buffer2, data_out_2, sizeof(data_out_2), &count_retrieved);
    elogInfo("Count Retr: %d", count_retrieved);

    for(i=0; i<8; i++)
    {
        uint32_t data = i;
        QuestFitCircularBuffer_put(circular_buffer2, &data);
    }
    QuestFitCircularBuffer_get(circular_buffer2, data_out_2, sizeof(data_out_2), &count_retrieved);
    elogInfo("Count Retr: %d", count_retrieved);

    for(i=0; i<1800; i++)
    {
        uint32_t data = i;
        QuestFitCircularBuffer_put(circular_buffer2, &data);
    }
    QuestFitCircularBuffer_get(circular_buffer2, data_out_2, sizeof(data_out_2), &count_retrieved);
    elogInfo("Count Retr: %d", count_retrieved);
    elogInfo("Freeing buffer");
    QuestFitCircularBuffer_free(circular_buffer2);
    return 0;
}
