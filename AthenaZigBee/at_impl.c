#include "at_impl.h"

#include <string.h>
#include "halpin.h"
#include "bits.h"

// WIN32 DEBUG
#ifndef __IAR_SYSTEMS_ICC__
#define __IAR_SYSTEMS_ICC__

int WIN32_ENV_P0 = 0;
int WIN32_ENV_P1 = 0;
int WIN32_ENV_P2 = 0;

#define P0 WIN32_ENV_P0
#define P1 WIN32_ENV_P1
#define P2 WIN32_ENV_P2

#endif // !__IAR_SYSTEMS_ICC__

// Check Pin Group is valid
#define _checkpin(grp, pin) (grp != PIN_INVALID && pin != PIN_INVALID)

// Bit mask group
const int BITMASKS[] = {BITM_0, BITM_1, BITM_2, BITM_3, BITM_4, BITM_5, BITM_6, BITM_7};

const uint onRebootHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_R));
	return RET_CODE_SUCCESS;
}

const uint onResetHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_Z));
	return RET_CODE_SUCCESS;
}

const uint onVersionHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_VER));
	return RET_CODE_SUCCESS;
}

const uint onRSSIHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_RSSI));
	return RET_CODE_SUCCESS;
}

const uint onMACHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_MAC));
	return RET_CODE_SUCCESS;
}

const uint onUARTHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_UART));
	return RET_CODE_SUCCESS;
}

const uint onNetworkAddHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_NWK));
	return RET_CODE_SUCCESS;
}

const uint onClearHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_CLEAR));
	return RET_CODE_SUCCESS;
}

const uint onTypeHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_TYPE));
	return RET_CODE_SUCCESS;
}

const uint onStatusHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_STAT));
	return RET_CODE_SUCCESS;
}

const uint onPanIdHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_PAN));
	return RET_CODE_SUCCESS;
}

const uint onChannelHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_CH));
	return RET_CODE_SUCCESS;
}

// GPIO
const uint onGPIOHandler(const struct atRequest * req, char* output) {
	if (_checkpin((*req).group, (*req).pin)) {
		if (_checkArgValid((*req).arg0)) { // [State] argument: Set state
			const int MASK = BITMASKS[(*req).arg0];
			if (0 == (*req).group) {
				((*req).arg0) ? SETBIT1_OF(P0, MASK) : SETBIT0_OF(P0, MASK);
			}
			else if (1 == (*req).group) {
				((*req).arg0) ? SETBIT1_OF(P1, MASK) : SETBIT0_OF(P1, MASK);
			}
			else {
				((*req).arg0) ? SETBIT1_OF(P2, MASK) : SETBIT0_OF(P2, MASK);
			}
			strcpy(output, RET_OK(NAME_AT_GPIO));
		}
		else { // No argument: Query state -> +GPIO=%d:L
			strcpy(output, "+GPIO=0:0:L");
			output[6] = _itonc((*req).group);
			output[8] = _itonc((*req).pin);
			char state;
			if (0 == (*req).group) {
				state = IS_BIT1_OF(P0, (*req).pin) ? 'H' : 'L';
			}
			else if (1 == (*req).group) {
				state = IS_BIT1_OF(P1, (*req).pin) ? 'H' : 'L';
			}
			else {
				state = IS_BIT1_OF(P2, (*req).pin) ? 'H' : 'L';
			}
			output[10] = state;
		}
	}
	else { // Query All pins: +GPIO=1:L,2:H,3:L
		strcpy(output, "+GPIO=1:1:L,2:2:H,0:3:L");
	}
	return RET_CODE_SUCCESS;
}

// Remote GPIO
const uint onRGPIOHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_RGPIO));
	return RET_CODE_SUCCESS;
}

// IO DIR
const uint onIODIRHandler(const struct atRequest * req, char* output) {
    if(_checkpin((*req).group, (*req).pin)) {
		if (_checkArgValid((*req).arg0)) {
			strcpy(output, RET_OK(NAME_AT_IODIR));
		}
		else {
			strcpy(output, "+IODIR=1:DI");
		}
	}
	else {
		strcpy(output, "+IODIR=1:DI,2:DO,3:DI");
	}
	return RET_CODE_SUCCESS;
}

// Remote IO DIR
const uint onRIODIRHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_RIODIR));
	return RET_CODE_SUCCESS;
}

const uint onINTHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_INT));
	return RET_CODE_SUCCESS;
}

const uint onRINTHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_RINT));
	return RET_CODE_SUCCESS;
}

const uint onPWMHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_PWM));
	return RET_CODE_SUCCESS;
}

const uint onRPWMHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_RPWM));
	return RET_CODE_SUCCESS;
}

const uint onADCHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_ADC));
	return RET_CODE_SUCCESS;
}

const uint onRADCMHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_RADC));
	return RET_CODE_SUCCESS;
}

const uint onConfPWMHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_CNF_PWM));
	return RET_CODE_SUCCESS;
}
