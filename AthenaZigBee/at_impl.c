#include <string.h>
#include "bits.h"
#include "cc2530.h"
#include "at_impl.h"

/////////////////10
// BASE=01234567890123456789
#define _idxGRPOf(startIdx, segSize, n)			((startIdx + 0) + (segSize * n) + (n ? n : 0))
#define _idxPINOf(startIdx, segSize, n)			((startIdx + 2) + (segSize * n) + (n ? n : 0))
#define _idxSTAOfN(startIdx, segSize, n, aN)	((startIdx + 5 + aN*3) + (segSize * n) + (n ? n : 0))


// Bit mask group
const int BITMASKS[] = { BITM_0, BITM_1, BITM_2, BITM_3, BITM_4, BITM_5, BITM_6, BITM_7 };

// Check Group&PinNumber is setted
#define _isSetPin(pin) (pin != AT_INVALID_PIN)
#define _isSetGrpPin(grp, pin) (grp != AT_INVALID_PIN && pin != AT_INVALID_PIN)

// Set Output with Arg0
#define _setBitMaskWithFlag(FLAG, T1, T2, T3) const int MASK = BITMASKS[req->pin];	\
	/*req.arg0 was checked*/												\
	if (0 == req->group) {												\
		(FLAG) ? SETBIT1_OF(T1, MASK) : SETBIT0_OF(T1, MASK);				\
	}																		\
	else if (1 == req->group) {											\
		(FLAG) ? SETBIT1_OF(T2, MASK) : SETBIT0_OF(T2, MASK);				\
	}																		\
	else {																	\
		(FLAG) ? SETBIT1_OF(T3, MASK) : SETBIT0_OF(T2, MASK);				\
	}																		\

// Set Output from REGISTER state,
// ARGN: If 0, Set group, pin to output.
#define _setOutputFromState(T1, T2, T3, SIDX, SEGLEN, IDX, ARGN, TRUEC, FALSEC)		;	\
	if(0 == ARGN) output[_idxGRPOf(SIDX, SEGLEN, IDX)] = _itonc(req->group);			\
	if(0 == ARGN) output[_idxPINOf(SIDX, SEGLEN, IDX)] = _itonc(req->pin);			\
	if (0 == req->group) {															\
		output[_idxSTAOfN(SIDX, SEGLEN, IDX, ARGN)] =									\
				IS_BIT1_OF(T1, req->pin) ? TRUEC : FALSEC;							\
	}																					\
	else if (1 == req->group) {														\
		output[_idxSTAOfN(SIDX, SEGLEN, IDX, ARGN)] =									\
				IS_BIT1_OF(T2, req->pin) ? TRUEC : FALSEC;							\
	}																					\
	else {																				\
		output[_idxSTAOfN(SIDX, SEGLEN, IDX, ARGN)] =									\
				IS_BIT1_OF(T3, req->pin) ? TRUEC : FALSEC;							\
	}																					\

////////////////////////////////////////////////

// Reboot device
void onRebootHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_R));
}

// Reset device settings
void onResetHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_Z));
}

// Kernal version
void onVersionHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_REPLY(NAME_AT_VER, "v2017.10M"));
}

// RSSI
void onRSSIHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_RSSI));
}

// MAC address
void onMACHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_MAC));
}

// UART configs
void onUARTHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_UART));
}

// Network
void onNetworkAddHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_NWK));
}

// Clear network config
void onClearHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_CLEAR));
}

// Device Type
void onDeviceTypeHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_TYPE));
}

// Device State
void onDeviceStateHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_STAT));
}

// PanId
void onPanIdHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_PAN));
}

// Channel
void onChannelHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_CH));
}

// GPIO: AT+GPIO=[G:P],[TL,TH]
void onGPIOHandler(const struct atRequest * req, char* output) {
	if (_isSetGrpPin(req->group, req->pin)) {
		if (_isSetArg(req->arg0)) { // [State] argument: Set state
			_setBitMaskWithFlag(req->arg0, P0, P1, P2);
			strcpy(output, RET_NAMED_OK(NAME_AT_GPIO));
		}
		else { // No argument: Query state
			strcpy(output, "+GPIO=_:_:T_");
			_setOutputFromState(P0, P1, P2,
				6,  // 6: Start Index Of "+GPIO="
				6,	// 6: Length of "0:0:TL"
				0,  // 0: Group Index of values array: "0:0:TL"
				0,	// 0: ArgumentIndex: "TL"
				ARG_C_TTL1, ARG_C_TTL0);
		}
	}
	else { // Query All pins: +GPIO=1:L,2:TH,3:TL
		strcpy(output, "+GPIO=ALL_STATE_NOT_SUPPORTED");
	}
}

// Remote GPIO
void onRGPIOHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_RGPIO));
}

// Config IO PUll
void onIOPullHandler(const struct atRequest * req, char* output) {
	// AT+IOPULL=[G],[PU, PD]
	if (_isSetPin(req->group)) {
		if (_isSetArg(req->arg0)) {
			switch (req->group) {
			case 0:
				(req->arg0) ? SETBIT1_OF(P2INP, BITM_5) : SETBIT0_OF(P2INP, BITM_5);
				break;
			case 1:
				(req->arg0) ? SETBIT1_OF(P2INP, BITM_6) : SETBIT0_OF(P2INP, BITM_6);
				break;
			default:
				(req->arg0) ? SETBIT1_OF(P2INP, BITM_7) : SETBIT0_OF(P2INP, BITM_7);
				break;
			}
			strcpy(output, RET_NAMED_OK(NAME_AT_IOPULL));
		}// Query
		else {
			strcpy(output, "+IOPULL=_:P_");
			output[8] = _itonc(req->group);
			char pc;
			switch (req->group) {
			case 0:
				pc = (IS_BIT1_OF(P2INP, 5) ? ARG_C_PULL1 : ARG_C_PULL0);
				break;
			case 1:
				pc = (IS_BIT1_OF(P2INP, 6) ? ARG_C_PULL1 : ARG_C_PULL0);
				break;
			default:
				pc = (IS_BIT1_OF(P2INP, 7) ? ARG_C_PULL1 : ARG_C_PULL0);
				break;
			}
			output[11] = pc;
		}
	}
	else {
		strcpy(output, "+IOPULL=ALL_IOPULL_NOT_SUPPORTED");
	}
}

// IO DIR:
void onIODIRHandler(const struct atRequest * req, char* output) {
	// AT+IODIR = [G:P], [DI, DO], [MP, MN]
    if(_isSetGrpPin(req->group, req->pin)) {
		if (_isSetArg(req->arg0)) {
			// IO DIR£º [DI, DO]
			_setBitMaskWithFlag(req->arg0, P0DIR, P1DIR, P2DIR);
			// Dir IN, set mode
			if (ARG_N_DIRIN == req->arg0 && _isSetArg(req->arg1)) {
				_setBitMaskWithFlag(req->arg1, P0INP, P1INP, P2INP);
			}
			strcpy(output, RET_NAMED_OK(NAME_AT_IODIR));
		}
		else {// Query
			strcpy(output, "+IODIR=_:_:D_:M_");
			// Direction
			_setOutputFromState(P0DIR, P1DIR, P2DIR,
				7,  // 7: Start Index Of "+IODIR="
				9,  // 9: Length of "_:_:D_:P_"
				0,  // 0: Group Index of values array: "_:_:D_:P_"
				0,	// 0: Argument Index of "D_"
				ARG_C_DIR1, ARG_C_DIR0);
			// In Mode
			_setOutputFromState(P0INP, P1INP, P2INP,
				7,  // 7: Start Index Of "+IODIR="
				9,  // 9: Length of "_:_:D_:M_"
				0,  // 0: Group Index of values array: "_:_:D_:M_"
				1,	// 1: Argument Index of "M_"
				ARG_C_MODE1, ARG_C_MODE0);
		}
	}
	else {
		strcpy(output, "+IODIR=ALL_IODIR_NOT_SUPPORTED");
	}
}

// Remote IO DIR
void onRIODIRHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_RIODIR));
}

// Interruptor trigger cofig
void onINTTriggerHandler(const struct atRequest * req, char* output) {
	// AT+INTTRI=[GROUP],[PULL]
	if (_isSetPin(req->group)) {
		if (_isSetArg(req->arg0)) {
			switch (req->group) {
			case 0:
				(req->arg0) ? SETBIT1_OF(PICTL, BITM_0) : SETBIT0_OF(PICTL, BITM_0);
				break;
			case 1:
				(req->arg0) ? SETBIT1_OF(PICTL, BITM_1) : SETBIT0_OF(PICTL, BITM_1);
				(req->arg0) ? SETBIT1_OF(PICTL, BITM_2) : SETBIT0_OF(PICTL, BITM_2);
				break;
			default:
				(req->arg0) ? SETBIT1_OF(PICTL, BITM_3) : SETBIT0_OF(PICTL, BITM_3);
				break;
			}
			strcpy(output, RET_NAMED_OK(NAME_AT_INTTRI));
		}
		else {
			strcpy(output, "+INTTRI=_:P_");
			output[8] = _itonc(req->group);
			char pc;
			switch (req->group) {
			case 0:
				pc = (IS_BIT1_OF(PICTL, 0) ? ARG_C_PULL1 : ARG_C_PULL0);
				break;
			case 1:
				pc = (IS_BIT1_OF(PICTL, 1) ? ARG_C_PULL1 : ARG_C_PULL0);
				break;
			default:
				pc = (IS_BIT1_OF(PICTL, 3) ? ARG_C_PULL1 : ARG_C_PULL0);
				break;
			}
			output[11] = pc;
		}
	}
	else {
		strcpy(output, "+IODIR=ALL_INTTRI_NOT_SUPPORTED");
	}
}

// INT service
void onINTHandler(const struct atRequest * req, char* output) {
	// AT+INT=[G:P],[SE,SD]
	if (_isSetGrpPin(req->group, req->pin)) {
		if (_isSetArg(req->arg0)) {
			// INT State£º [SE, SD]
			_setBitMaskWithFlag(req->arg0, P0IEN, P1IEN, P2IEN);
			strcpy(output, RET_NAMED_OK(NAME_AT_INT));
		}
		else {// Query
			strcpy(output, "+INT=_:_:S_");
			// INT State
			_setOutputFromState(P0IEN, P1IEN, P2IEN,
				5,  // 5: Start Index Of "+IODIR="
				6,  // 6: Length of "_:_:D_:P_"
				0,  // 0: Group Index of values array: "_:_:S_"
				0,	// 0: Argument Index of "S_"
				ARG_C_STATE1, ARG_C_STATE0);
		}
	}
	else {
		strcpy(output, "+INT=ALL_INT_NOT_SUPPORTED");
	}
}

void onRINTHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_RINT));
}

// PWM Config
void onConfPWMHandler(const struct atRequest * req, char* output) {
	strcpy(output, RET_NAMED_OK(NAME_AT_INTTRI));
}

void onPWMHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_PWM));
}

void onRPWMHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_RPWM));
}

void onADCHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_ADC));
}

void onRADCMHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_NAMED_OK(NAME_AT_RADC));
}
