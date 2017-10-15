#include <string.h>
#include "util.h"
#include "uart.h"
#include "at_impl.h"

char buffResponse[AT_BUFF_RESPONSE_SIZE] = { 0 };
char buffRequest[AT_BUFF_REQUEST_SIZE] = { 0 };
uint requestReadIndex = 0;

#define _isReceivedATCommandEnd(c)		('/0' == c || '\r' == c || '\n' == c)

// Init AT system, register handlers.
void registerATKernal() {
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
	// Reset buffer
	memset(buffResponse, '\0', strlen(buffResponse));
	unsigned int atLen = checkAT(command);
	if (atLen > 0) {
		struct atRequest request;
		parseAT(&request, atLen, command);
		if (RET_CODE_SUCCESS == request.status && request.index >= 0) {
#ifdef _WIN32
			printf("-> AT.CMD : %s\n", command);
			printf("-> REQUEST: idx: %d, group: %d, pin: %d, arg0: %d, arg1: %d, arg2: %d \n",
				request.index, request.group, request.pin, request.arg0, request.arg1, request.arg2);
#endif
			// Process AT Request and get output			
			handleAT(&request, buffResponse);
		}
		else {
			strcpy(buffResponse,
				(RET_CODE_ARGUMENT == request.status)
					? (RET_ERRMSG_ARGS)
					: (RET_NAMED_UNSUP("BAD_STAT,BAD_AT")));
		}
	}
	else {
		strcpy(buffResponse, RET_NAMED_UNSUP("BAD_AT:LEN:0"));
	}
#ifdef _WIN32
	printf("--> HANDLED: \n\t%s\n\n", buffResponse);
#else
	uartSend(buffResponse, strlen(buffResponse));
#endif
}

// Receive
void uartReqestListener(char received) {
	if ((requestReadIndex >= AT_REQUEST_MAX_LEN || _isReceivedATCommandEnd(received))
		&& requestReadIndex > 0) {
		// ECHO
		// uartSend(buffRequest, strlen(buffRequest));
		processATRequest(buffRequest);
		memset(buffRequest, '\0', strlen(buffRequest));
		requestReadIndex = 0;
	}
	else {
		// 单个字符必须是以 A 开头才开始接收
		if (requestReadIndex == 0 && 'A' != received) {
			return;
		}
		buffRequest[requestReadIndex] = received;
		requestReadIndex++;
	}
}

void main(void) {
	// Register AT Handler
	registerATKernal();
	// UART
	uartInit();
	// UART Listener
	uartListener(uartReqestListener);
	// Test
	processATRequest("AT+VER");
#ifdef _WIN32
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
	while (1);
#endif // WINDOWS
}