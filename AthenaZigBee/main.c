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

	registerAT(KEY_AT_CNF_INM, onConfInModeHandler);
	registerAT(KEY_AT_IODIR, onIODIRHandler);
	registerAT(KEY_AT_RIODIR, onRIODIRHandler);

	registerAT(KEY_AT_CNF_INT, onConfINTHandler);
	registerAT(KEY_AT_INT, onINTHandler);
	registerAT(KEY_AT_RINT, onRINTHandler);

	registerAT(KEY_AT_CNF_PWM, onConfPWMHandler);
	registerAT(KEY_AT_PWM, onPWMHandler);
	registerAT(KEY_AT_RPWM, onRPWMHandler);

	registerAT(KEY_AT_ADC, onADCHandler);
	registerAT(KEYAT_RADC, onRADCMHandler);
}

// Process AT command request
void processATRequest(pchar at) {
	unsigned int len = checkAT(at);
	if (len > 0) {
		char output[AT_RESULT_BUFF] = { 0 };
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


/////////////////10
// BASE=01234567890123456789
// +GPIO=A:B:_C:_D,A:B:_C:_D,
// (startIdx + N): Start position of the segment value
// (segSize * N):
// ()
#define aIDX_GRP_OF(startIdx, segSize, n)		((startIdx + 0) + (segSize * n) + (n ? n : 0))
#define aIDX_PIN_OF(startIdx, segSize, n)		((startIdx + 2) + (segSize * n) + (n ? n : 0))
#define aIDX_STA0_OF(startIdx, segSize, n)		((startIdx + 5) + (segSize * n) + (n ? n : 0))
#define aIDX_STA1_OF(startIdx, segSize, n)		((startIdx + 8) + (segSize * n) + (n ? n : 0))


void main(void) {
	initATSystem();

	//char output[] = "+IODIR=0:0:_0";
	//char output[] = "+GPIO=0:0:_0:_0,1:1:_1:_1,2:2:_2:_2,3:3:_3:_3";
	//output[aIDX_GRP_OF(7, 6, 0)] = 'A';
	//output[aIDX_PIN_OF(7, 6, 0)] = 'A';
	//output[aIDX_STA0_OF(7, 6, 0)] = 'A';
	// output[aIDX_STA1_OF(6, 9, 0)] = 'A';
	/*
	output[aIDX_GRP_OF(6, 9, 1)] = 'B';
	output[aIDX_PIN_OF(6, 9, 1)] = 'B';
	output[aIDX_STA0_OF(6, 9, 1)] = 'B';
	output[aIDX_STA1_OF(6, 9, 1)] = 'B';

	output[aIDX_GRP_OF(6, 9, 2)] = 'C';
	output[aIDX_PIN_OF(6, 9, 2)] = 'C';
	output[aIDX_STA0_OF(6, 9, 2)] = 'C';
	output[aIDX_STA1_OF(6, 9, 2)] = 'C';

	output[aIDX_GRP_OF(6, 9, 3)] = 'D';
	output[aIDX_PIN_OF(6, 9, 3)] = 'D';
	output[aIDX_STA0_OF(6, 9, 3)] = 'D';
	output[aIDX_STA1_OF(6, 9, 3)] = 'D';
	*/
	//printf("--> %s\n", output);


#ifdef _WIN32

	processATRequest("AT+VER");
/*
	processATRequest("AT+GPIO=1:4,TL");
	processATRequest("AT+GPIO=1:4");
	processATRequest("AT+GPIO=1:4,TH");
	processATRequest("AT+GPIO=1:4");
*/
	processATRequest("AT+IODIR=1:4,DI,MP");
	processATRequest("AT+IODIR=1:4");
	processATRequest("AT+IODIR=1:4,DO,MN");
	processATRequest("AT+IODIR=1:4");

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
