#include "at_impl.h"

#include "hal_pin.h"
#include "bits.h"


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
	if (req.pin != PIN_INVALID) {
		if (_IS_ARGX_VALID(req.arg0)) { // [State] argument: Set state
			// TODO
			return RET_OK(NAME_AT_GPIO);
		}
		else { // No argument: Query state -> +GPIO=%d:L
			return "+GPIO=1:L";
		}
	}
	else { // Query All pins: +GPIO=1:L,2:H,3:L
		return "+GPIO=1:1:L,2:2:H,0:3:L";
	}
}

// Remote GPIO
pchar onRGPIOHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RGPIO);
}

// IO DIR
pchar onIODIRHandler(struct atRequest req) {
    if(req.pin != PIN_INVALID) {
		if (_IS_ARGX_VALID(req.arg0)) {
			return RET_OK(NAME_AT_IODIR);
		}
		else {
			return "+IODIR=1:DI";
		}
	}
	else {
		return "+IODIR=1:DI,2:DO,3:DI";
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
