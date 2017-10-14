#include "at_impl.h"

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

pchar onRebootHandler(struct atRequest req) {
    return RET_OK(NAME_AT_R);
}

pchar onResetHandler(struct atRequest req) {
    return RET_OK(NAME_AT_Z);
}

pchar onVersionHandler(struct atRequest req) {
    return RET_OK(NAME_AT_VER);
}

pchar onRSSIHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RSSI);
}

pchar onMACHandler(struct atRequest req) {
    return RET_OK(NAME_AT_MAC);
}

pchar onUARTHandler(struct atRequest req) {
    return RET_OK(NAME_AT_UART);
}

pchar onNetworkAddHandler(struct atRequest req) {
    return RET_OK(NAME_AT_NWK);
}

pchar onClearHandler(struct atRequest req) {
    return RET_OK(NAME_AT_CLEAR);
}

pchar onTypeHandler(struct atRequest req) {
    return RET_OK(NAME_AT_TYPE);
}

pchar onStatusHandler(struct atRequest req) {
    return RET_OK(NAME_AT_STAT);
}

pchar onPanIdHandler(struct atRequest req) {
    return RET_OK(NAME_AT_PAN);
}

pchar onChannelHandler(struct atRequest req) {
    return RET_OK(NAME_AT_CH);
}

// GPIO
pchar onGPIOHandler(struct atRequest req) {
	if (_checkpin(req.group, req.pin)) {
		if (_IS_ARGX_VALID(req.arg0)) { // [State] argument: Set state
			const int MASK = BITMASKS[req.arg0];
			if (0 == req.group) {
				(req.arg0) ? SETBIT1_OF(P0, MASK) : SETBIT0_OF(P0, MASK);
			}
			else if (1 == req.group) {
				(req.arg0) ? SETBIT1_OF(P1, MASK) : SETBIT0_OF(P1, MASK);
			}
			else {
				(req.arg0) ? SETBIT1_OF(P2, MASK) : SETBIT0_OF(P2, MASK);
			}
			return RET_OK(NAME_AT_GPIO);
		}
		else { // No argument: Query state -> +GPIO=%d:L
			char output[] = "+GPIO=0:0:L";
			output[6] = req.group + '0';
			output[8] = req.pin + '0';
			char state;
			if (0 == req.group) {
				state = IS_BIT1_OF(P0, req.pin) ? 'H' : 'L';
			}
			else if (1 == req.group) {
				state = IS_BIT1_OF(P1, req.pin) ? 'H' : 'L';
			}
			else {
				state = IS_BIT1_OF(P2, req.pin) ? 'H' : 'L';
			}
			output[10] = state;
			return output;
		}
	}
	else { // Query All pins: +GPIO=1:L,2:H,3:L
		return "+GPIO=1:1:L,2:2:H,0:3:L\n";
	}
}

// Remote GPIO
pchar onRGPIOHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RGPIO);
}

// IO DIR
pchar onIODIRHandler(struct atRequest req) {
    if(_checkpin(req.group, req.pin)) {
		if (_IS_ARGX_VALID(req.arg0)) {
			return RET_OK(NAME_AT_IODIR);
		}
		else {
			return "+IODIR=1:DI\n";
		}
	}
	else {
		return "+IODIR=1:DI,2:DO,3:DI\n";
	}

}

// Remote IO DIR
pchar onRIODIRHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RIODIR);
}

pchar onINTHandler(struct atRequest req) {
    return RET_OK(NAME_AT_INT);
}

pchar onRINTHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RINT);
}

pchar onPWMHandler(struct atRequest req) {
    return RET_OK(NAME_AT_PWM);
}

pchar onRPWMHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RPWM);
}

pchar onADCHandler(struct atRequest req) {
    return RET_OK(NAME_AT_ADC);
}

pchar onRADCMHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RADC);
}

pchar onConfPWMHandler(struct atRequest req) {
    return RET_OK(NAME_AT_CNF_PWM);
}
