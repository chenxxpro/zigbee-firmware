#ifndef ioint_h
#define ioint_h

#include "types.h"

// TTL Changed Listener
typedef void(*TTLListener)(uint group, uint pin, uchar ttl);

// Set Listener
void setIOINTListener(TTLListener listener);

// Init
void iointInit();

#endif

