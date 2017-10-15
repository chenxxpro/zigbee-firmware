#ifndef uart_h
#define uart_h

#include "types.h"

typedef void(*UartListener)(char received);

// Init UART
void uartInit();

// Send String to UART
void uartSend(char* data, const uint len);

// 
void uartListener(UartListener listener);

#endif /* uart_h */