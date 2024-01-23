
#include <stdbool.h>

extern int QuestFitNetworkComm_connect();
extern int QuestFitNetworkComm_Destroy();
extern bool QuestFitNetworkComm_is_connected();

extern int QuestFitNetworkComm_discover_pe();
extern int QuestFitNetworkComm_publish_message(const char *topic, void *payload, size_t payloadlen);
