#include "at_impl.h"

#include <string.h>
#include "halpin.h"
#include "bits.h"

// WIN32 DEBUG
#ifdef _WIN32

extern int WIN32_ENV_P0 = 0;
extern int WIN32_ENV_P1 = 0;
extern int WIN32_ENV_P2 = 0;
extern int WIN32_ENV_P0DIR = 0;
extern int WIN32_ENV_P1DIR = 0;
extern int WIN32_ENV_P2DIR = 0;

#define P0 WIN32_ENV_P0
#define P1 WIN32_ENV_P1
#define P2 WIN32_ENV_P2

#define P0DIR WIN32_ENV_P0DIR
#define P1DIR WIN32_ENV_P1DIR
#define P2DIR WIN32_ENV_P2DIR

#else

#include <ioCC2530.h>

#endif // !__IAR_SYSTEMS_ICC__

// Check Pin Group is valid
#define _checkpin(grp, pin) (grp != PIN_INVALID && pin != PIN_INVALID)

#define IDX_GRP_OF(b, n)	(b+0 + b * n)
#define IDX_PIN_OF(b, n)	(b+2 + b * n)
#define IDX_STA_OF(b, n)	(b+5 + b * n)

#define IDX_GPIO_GRP(n)		IDX_GRP_OF(6, n)
#define IDX_GPIO_PIN(n)		IDX_PIN_OF(6, n)
#define IDX_GPIO_STA(n)		IDX_STA_OF(6, n)

#define IDX_IODIR_GRP(n)	IDX_GRP_OF(7, n)
#define IDX_IODIR_PIN(n)	IDX_PIN_OF(7, n)
#define IDX_IODIR_STA(n)	IDX_STA_OF(7, n)


///// Check Pin Group, Set state with bitmask
#define _setbitmask(T1, T2, T3) const int MASK = BITMASKS[(*req).pin];		\
	if (0 == (*req).group) {												\
		((*req).arg0) ? SETBIT1_OF(T1, MASK) : SETBIT0_OF(T1, MASK);		\
	}																		\
	else if (1 == (*req).group) {											\
		((*req).arg0) ? SETBIT1_OF(T2, MASK) : SETBIT0_OF(T2, MASK);		\
	}																		\
	else {																	\
		((*req).arg0) ? SETBIT1_OF(T3, MASK) : SETBIT0_OF(T2, MASK);		\
	}																		\

/////
#define _setoutput(T1, T2, T3, BASE, IDX, TRUEC, FALSEC) char state;\
	output[IDX_GRP_OF(BASE, IDX)] = _itonc((*req).group);		\
	output[IDX_PIN_OF(BASE, IDX)] = _itonc((*req).pin);			\
	if (0 == (*req).group) {									\
		state = IS_BIT1_OF(T1, (*req).pin) ? TRUEC : FALSEC;	\
	}															\
	else if (1 == (*req).group) {								\
		state = IS_BIT1_OF(T2, (*req).pin) ? TRUEC : FALSEC;	\
	}															\
	else {														\
		state = IS_BIT1_OF(T3, (*req).pin) ? TRUEC : FALSEC;	\
	}															\
	output[IDX_STA_OF(BASE, IDX)] = state;							\

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
    strcpy(output, RET_REPLY(NAME_AT_VER, "v2017.10M"));
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
			_setbitmask(P0, P1, P2);
			strcpy(output, RET_OK(NAME_AT_GPIO));
		}
		else { // No argument: Query state -> +GPIO=%d:L
			strcpy(output, "+GPIO=0:0:TL");
			// 6: sizeof("+GPIO=")
			// 0: index of value segment: "0:0:L"
			_setoutput(P0, P1, P2, 6, 0, 'H', 'L');
		}
	}
	else { // Query All pins: +GPIO=1:L,2:H,3:L
		strcpy(output, "+GPIO=ALL_STATE_NOT_SUPPORTED");
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
			_setbitmask(P0DIR, P1DIR, P2DIR);
			strcpy(output, RET_OK(NAME_AT_IODIR));
		}
		else {
			strcpy(output, "+IODIR=0:0:DI");
			_setoutput(P0DIR, P1DIR, P2DIR,
				7,  // 7: sizeof("+IODIR=")
				0,  // 0: index of value segment: "0:0:L"
				'O', 'I');
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
