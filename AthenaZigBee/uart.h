#ifndef uart_h
#define uart_h

#include "types.h"

void uartInit();

void uartSend(char* data, const uint len);

uint uartReceive(char* buff);

#endif /* uart_h */