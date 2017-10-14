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
	registerAT(KEY_AT_TYPE, onTypeHandler);
	registerAT(KEY_AT_STAT, onStatusHandler);
	registerAT(KEY_AT_PAN, onPanIdHandler);
	registerAT(KEY_AT_CH, onChannelHandler);
	registerAT(KEY_AT_GPIO, onGPIOHandler);
	registerAT(KEY_AT_RGPIO, onRGPIOHandler);
	registerAT(KEY_AT_IODIR, onIODIRHandler);
	registerAT(KEY_AT_RIODIR, onRIODIRHandler);
	registerAT(KEY_AT_INT, onINTHandler);
	registerAT(KEY_AT_RINT, onRINTHandler);
	registerAT(KEY_AT_PWM, onPWMHandler);
	registerAT(KEY_AT_RPWM, onRPWMHandler);
	registerAT(KEY_AT_ADC, onADCHandler);
	registerAT(KEYAT_RADC, onRADCMHandler);
	registerAT(KEY_AT_CNF_PWM, onConfPWMHandler);
}

// Process AT command request
void processATRequest(pchar at) {
	unsigned int len = checkAT(at);
	if (len > 0) {
		struct atRequest req = parseAT(len, at);
		if (ERR_CODE_NONE == req.error && req.index >= 0) {
			printf("-> Handle REQUEST: \n\t idx: %d, group: %d, pin: %d, arg0: 0x%X, arg1: 0x%X, arg2: 0x%X \n", 
				req.index, 
				req.group, req.pin, 
				req.arg0, req.arg1, req.arg2);
			_log(handleAT(req));
		}
		else {
			_log((ERR_CODE_ARGUMENT == req.error) ? (RET_ERR_ARGS) : (RET_ERR_UNSUP));
		}
	}
	else {
		_log(RET_ERR_UNSUP);
	}
}

void main(void) {
	initATSystem();
	processATRequest("AT+R");
	processATRequest("AT+VER=");
	processATRequest("AT+PWM=0:2");
	processATRequest("AT+GPIO=1:4");
	processATRequest("AT+GPIO=1:4,H");
	processATRequest("AT+INT=1:6,EN,DU");
	processATRequest("AT+RINT=2:1,DIS,DU,85");
	processATRequest("AT+CNF_PWM=90");
	getchar();
}
