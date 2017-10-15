#include <string.h>
#include "bits.h"
#include "at_impl.h"

// WIN32 DEBUG
#ifdef _WIN32

// Pin Group
extern int WIN32_P0 = 0;
extern int WIN32_P1 = 0;
extern int WIN32_P2 = 0;
#define P0 WIN32_P0
#define P1 WIN32_P1
#define P2 WIN32_P2

// Pin IO Dir
extern int WIN32_P0DIR = 0;
extern int WIN32_P1DIR = 0;
extern int WIN32_P2DIR = 0;
#define P0DIR WIN32_P0DIR
#define P1DIR WIN32_P1DIR
#define P2DIR WIN32_P2DIR

// Pin Pull State
extern int WIN32_P0INP = 0;
extern int WIN32_P1INP = 0;
extern int WIN32_P2INP = 0;
#define P0INP WIN32_P0INP
#define P1INP WIN32_P1INP
#define P2INP WIN32_P2INP

// Pin Intertuptors
extern int WIN32_IEN0 = 0;
extern int WIN32_IEN1 = 0;
extern int WIN32_IEN2 = 0;
#define IEN0 WIN32_IEN0
#define IEN1 WIN32_IEN1
#define IEN2 WIN32_IEN2
extern int WIN32_P0IEN = 0;
extern int WIN32_P1IEN = 0;
extern int WIN32_P2IEN = 0;
#define P0IEN WIN32_P0IEN
#define P1IEN WIN32_P1IEN
#define P2IEN WIN32_P2IEN
extern int WIN32_PICTL = 0;
#define PICTL WIN32_PICTL

#else

#include <ioCC2530.h>

#endif // !_WIN32

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
const uint onRebootHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_R));
	return RET_CODE_SUCCESS;
}

// Reset device settings
const uint onResetHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_Z));
	return RET_CODE_SUCCESS;
}

// Kernal version
const uint onVersionHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_REPLY(NAME_AT_VER, "v2017.10M"));
	return RET_CODE_SUCCESS;
}

// RSSI
const uint onRSSIHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_RSSI));
	return RET_CODE_SUCCESS;
}

// MAC address
const uint onMACHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_MAC));
	return RET_CODE_SUCCESS;
}

// UART configs
const uint onUARTHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_UART));
	return RET_CODE_SUCCESS;
}

// Network
const uint onNetworkAddHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_NWK));
	return RET_CODE_SUCCESS;
}

// Clear network config
const uint onClearHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_CLEAR));
	return RET_CODE_SUCCESS;
}

// Device Type
const uint onDeviceTypeHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_TYPE));
	return RET_CODE_SUCCESS;
}

// Device State
const uint onDeviceStateHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_STAT));
	return RET_CODE_SUCCESS;
}

// PanId
const uint onPanIdHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_PAN));
	return RET_CODE_SUCCESS;
}

// Channel
const uint onChannelHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_CH));
	return RET_CODE_SUCCESS;
}

// GPIO: AT+GPIO=[G:P],[TL,TH]
const uint onGPIOHandler(const struct atRequest * req, char* output) {
	if (_isSetGrpPin(req->group, req->pin)) {
		if (_isSetArg(req->arg0)) { // [State] argument: Set state
			_setBitMaskWithFlag(req->arg0, P0, P1, P2);
			strcpy(output, RET_OK(NAME_AT_GPIO));
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
	return RET_CODE_SUCCESS;
}

// Remote GPIO
const uint onRGPIOHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_RGPIO));
	return RET_CODE_SUCCESS;
}

// Config IO PUll
const uint onIOPullHandler(const struct atRequest * req, char* output) {
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
			strcpy(output, RET_OK(NAME_AT_IOPULL));
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
	return RET_CODE_SUCCESS;
}

// IO DIR: 
const uint onIODIRHandler(const struct atRequest * req, char* output) {
	// AT+IODIR = [G:P], [DI, DO], [MP, MN]
    if(_isSetGrpPin(req->group, req->pin)) {
		if (_isSetArg(req->arg0)) {
			// IO DIR£º [DI, DO]
			_setBitMaskWithFlag(req->arg0, P0DIR, P1DIR, P2DIR);
			// Dir IN, set mode
			if (ARG_N_DIRIN == req->arg0 && _isSetArg(req->arg1)) {
				_setBitMaskWithFlag(req->arg1, P0INP, P1INP, P2INP);
			}
			strcpy(output, RET_OK(NAME_AT_IODIR));
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
	return RET_CODE_SUCCESS;
}

// Remote IO DIR
const uint onRIODIRHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_RIODIR));
	return RET_CODE_SUCCESS;
}

// Interruptor trigger cofig
const uint onINTTriggerHandler(const struct atRequest * req, char* output) {
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
			strcpy(output, RET_OK(NAME_AT_INTTRI));
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
	return RET_CODE_SUCCESS;
}

// INT service
const uint onINTHandler(const struct atRequest * req, char* output) {
	// AT+INT=[G:P],[SE,SD]
	if (_isSetGrpPin(req->group, req->pin)) {
		if (_isSetArg(req->arg0)) {
			// INT State£º [SE, SD]
			_setBitMaskWithFlag(req->arg0, P0IEN, P1IEN, P2IEN);
			strcpy(output, RET_OK(NAME_AT_INT));
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
	return RET_CODE_SUCCESS;
}

const uint onRINTHandler(const struct atRequest * req, char* output) {
    strcpy(output, RET_OK(NAME_AT_RINT));
	return RET_CODE_SUCCESS;
}

// PWM Config
const uint onConfPWMHandler(const struct atRequest * req, char* output) {
	strcpy(output, RET_OK(NAME_AT_INTTRI));
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
