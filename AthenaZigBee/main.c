
#include <string.h>
#include "util.h"
#include "uart.h"
#include "at_impl.h"

char BUFF_OUTPUT[AT_OUTPUT_BUFF_SIZE] = { 0 };

// Init AT system, register handlers.
void initATSystem() {
	registerAT(KEY_AT_R, onRebootHandler);
	registerAT(KEY_AT_Z, onResetHandler);
	registerAT(KEY_AT_VER, onVersionHandler);
	registerAT(KEY_AT_RSSI, onRSSIHandler);
	registerAT(KEY_AT_MAC, onMACHandler);

	registerAT(KEY_AT_UART, onUARTHandler);
	registerAT(KEY_AT_NWK, onNetworkAddHandler);
	registerAT(KEY_AT_CLEAR, onClearHandler);
	registerAT(KEY_AT_TYPE, onDeviceTypeHandler);
	registerAT(KEY_AT_STAT, onDeviceStateHandler);
	registerAT(KEY_AT_PAN, onPanIdHandler);
	registerAT(KEY_AT_CH, onChannelHandler);

	registerAT(KEY_AT_GPIO, onGPIOHandler);
	registerAT(KEY_AT_RGPIO, onRGPIOHandler);

	registerAT(KEY_AT_IOPULL, onIOPullHandler);
	registerAT(KEY_AT_IODIR, onIODIRHandler);
	registerAT(KEY_AT_RIODIR, onRIODIRHandler);

	registerAT(KEY_AT_INTTRI, onINTTriggerHandler);
	registerAT(KEY_AT_INT, onINTHandler);
	registerAT(KEY_AT_RINT, onRINTHandler);

	registerAT(KEY_AT_CNF_PWM, onConfPWMHandler);
	registerAT(KEY_AT_PWM, onPWMHandler);
	registerAT(KEY_AT_RPWM, onRPWMHandler);

	registerAT(KEY_AT_ADC, onADCHandler);
	registerAT(KEY_AT_RADC, onRADCMHandler);
}

// Process AT command request
void processATRequest(pchar command) {
	unsigned int atlen = checkAT(command);
	if (atlen > 0) {
		struct atRequest request;
		parseAT(&request, atlen, command);
		if (RET_CODE_SUCCESS == request.error && request.index >= 0) {
#ifdef _WIN32
			printf("-> AT.CMD : %s\n", command);
			printf("-> REQUEST: idx: %d, group: %d, pin: %d, arg0: %d, arg1: %d, arg2: %d \n",
				request.index, request.group, request.pin, request.arg0, request.arg1, request.arg2);
#endif
			// Process AT Request and get output
			const uint code = handleAT(&request, BUFF_OUTPUT);
#ifdef _WIN32
            printf("#### HANDLED(%d): \n\t%s\n\n", code, BUFF_OUTPUT);
#else
            uartSend("ABC", 3);
#endif
			// Reset buffer
			memset(BUFF_OUTPUT, 0, AT_OUTPUT_BUFF_SIZE);
		}
		else {
			printf((RET_CODE_ARGUMENT == request.error) ? (RET_ERR_ARGS) : (RET_ERR_UNSUP));
		}
	}
	else {
		printf(RET_ERR_UNSUP);
	}
}

void main(void) {
	initATSystem();
	uartInit();

#ifdef _WIN32

	processATRequest("AT+VER");

	processATRequest("AT+INT=1:4,SE");
	processATRequest("AT+INT=1:4");
	processATRequest("AT+INT=1:4,SD");
	processATRequest("AT+INT=1:4");

	processATRequest("AT+IODIR=1:4,DI,MP");
	processATRequest("AT+IODIR=1:4");
	processATRequest("AT+IODIR=1:4,DO,MN");
	processATRequest("AT+IODIR=1:4");

	processATRequest("AT+INTTRI=1");
	processATRequest("AT+INTTRI=1,PD");
	processATRequest("AT+INTTRI=1");
	processATRequest("AT+INTTRI=1,PU");
	processATRequest("AT+INTTRI=1");

	getchar();

#else

	char atRequestBuf[AT_REQUEST_BUFF_SIZE] = { 0 };
	processATRequest("AT+IODIR=1:0,DO,PD");
	int networkLED = 0;
	while (1)
	{
		if (networkLED) {
			processATRequest("AT+GPIO=1:0,TL");
		}
		else {
			processATRequest("AT+GPIO=1:0,TH");
		}
		networkLED = ~networkLED;
        delay_ms(2000);
	}

#endif // WINDOWS
}