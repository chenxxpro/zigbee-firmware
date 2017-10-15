#include "util.h"
#include "at_impl.h"

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
void processATRequest(pchar at) {
	unsigned int len = checkAT(at);
	if (len > 0) {
		char output[AT_OUTPUT_BUFF_SIZE] = { 0 };
		struct atRequest req = parseAT(len, at);
		if (RET_CODE_SUCCESS == req.error && req.index >= 0) {
			printf("-> AT.CMD : %s\n", at);
			printf("-> REQUEST: idx: %d, group: %d, pin: %d, arg0: %d, arg1: %d, arg2: %d \n",
				req.index, req.group, req.pin, req.arg0, req.arg1, req.arg2);
			const uint code = handleAT(&req, output);
			printf("#### HANDLED: \n\t%s\n\n", output);
		}
		else {
			printf((RET_CODE_ARGUMENT == req.error) ? (RET_ERR_ARGS) : (RET_ERR_UNSUP));
		}
	}
	else {
		printf(RET_ERR_UNSUP);
	}
}

void _delay_us(int ms) {
	while (ms--);
}

void main(void) {
	initATSystem();

#ifdef _WIN32

	processATRequest("AT+VER");

	processATRequest("AT+INT=1:4,SE");
	processATRequest("AT+INT=1:4");
	processATRequest("AT+INT=1:4,SD");
	processATRequest("AT+INT=1:4");
/*
	processATRequest("AT+IODIR=1:4,DI,MP");
	processATRequest("AT+IODIR=1:4");
	processATRequest("AT+IODIR=1:4,DO,MN");
	processATRequest("AT+IODIR=1:4");
	*/

	processATRequest("AT+INTTRI=1");
	processATRequest("AT+INTTRI=1,PD");
	processATRequest("AT+INTTRI=1");
	processATRequest("AT+INTTRI=1,PU");
	processATRequest("AT+INTTRI=1");

	getchar();

#else

	processATRequest("AT+IODIR=1:0,DO,PD");
	int stateOn = 0;
	while (0) {
		if (stateOn) {
			processATRequest("AT+GPIO=1:0,TH");
		}
		else {
			processATRequest("AT+GPIO=1:0,TL");
		}
		stateOn = ~stateOn;
		_delay_us(3000 * 10000);
	}

#endif // WINDOWS

}
