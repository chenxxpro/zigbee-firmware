#ifndef uart_h
#define uart_h

#include "types.h"

void uartInit();

void uartSend(pchar data, const uint len);

uint uartReceive(char* buff);

#endif /* uart_h */