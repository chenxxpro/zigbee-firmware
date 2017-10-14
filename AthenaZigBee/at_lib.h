#ifndef at_lib_h
#define at_lib_h

#include "types.h"

#define RET_ERR_UNSUP       "+ERR=AT_UNSUPPORT\n"
#define RET_ERR_ARGS       "+ERR=ARGUMENTS\n"
#define RET_OK(AT)          "+"AT"=OK\n"
#define RET_ERR_ARG(AT)     "+"AT"=ERR,ARGUMENTS\n"
#define RET_ERR_EXE(AT)     "+"AT"=ERR,RUNTIME\n"

#define RET_REPLY(AT,RET)   "+"AT"="RET"\n"

#define NAME_AT_R       "R"
#define NAME_AT_Z       "Z"
#define NAME_AT_VER     "VER"
#define NAME_AT_RSSI    "RSSI"
#define NAME_AT_MAC     "MAC"
#define NAME_AT_UART    "UART"
#define NAME_AT_TYPE    "TYPE"
#define NAME_AT_NWK     "NWK"
#define NAME_AT_CLEAR   "CLEAR"
#define NAME_AT_STAT    "STAT"
#define NAME_AT_PAN     "PAN"
#define NAME_AT_CH      "CH"
#define NAME_AT_GPIO    "GPIO"
#define NAME_AT_RGPIO   "RGPIO"
#define NAME_AT_IODIR   "IODIR"
#define NAME_AT_RIODIR  "RIODIR"
#define NAME_AT_INT     "INT"
#define NAME_AT_RINT    "RINT"
#define NAME_AT_PWM     "PWM"
#define NAME_AT_RPWM    "RPWM"
#define NAME_AT_ADC     "ADC"
#define NAME_AT_RADC    "RADC"
#define NAME_AT_CNF_PWM "CNF_PWM"

#define KEY_AT_R       0
#define KEY_AT_Z       1
#define KEY_AT_VER     2
#define KEY_AT_RSSI    3
#define KEY_AT_MAC     4
#define KEY_AT_UART    5
#define KEY_AT_TYPE    6
#define KEY_AT_NWK     7
#define KEY_AT_CLEAR   8
#define KEY_AT_STAT    9
#define KEY_AT_PAN     10
#define KEY_AT_CH      11
#define KEY_AT_GPIO    12
#define KEY_AT_RGPIO   13
#define KEY_AT_IODIR   14
#define KEY_AT_RIODIR  15
#define KEY_AT_INT     16
#define KEY_AT_RINT    17
#define KEY_AT_PWM     18
#define KEY_AT_RPWM    19
#define KEY_AT_ADC     20
#define KEYAT_RADC     21
#define KEY_AT_CNF_PWM 22

#define AT_CMD_SIZE     23

#define AT_CMD_IPREFIX  3
#define AT_CMD_MIN_LEN  4
#define AT_CMD_MAX_LEN  9

#define AT_SEG_MAX_LEN  7
#define AT_SEG_BUF_LEN  AT_SEG_MAX_LEN + 1

#define AT_ARG_MAX_LEN  3
#define AT_ARG_BUF_LEN  AT_ARG_MAX_LEN + 1

#define ERR_CODE_NONE		0
#define ERR_CODE_UNSUPPORT	1
#define ERR_CODE_ARGUMENT	2


// AT request command struct
struct atRequest {
	// Error code	
    uchar err;

	// AT command Index
	uint index;

	// Pin number
	uint pin;

	// Arg 0
	uint arg0;

	// Arg 1
	uchar arg1;

	// Arg 2
	uchar arg2;
};

// AT command handler
typedef pchar (*atHandler)(struct atRequest req);

// check if AT Command is valid
const uint checkAT(pchar at);

// parseAT command to request struct
const struct atRequest parseAT(const uint len, pchar command);

// register AT command handler
void registerAT(const int index, const atHandler handler);

// handle AT request
pchar handleAT(const struct atRequest req);

#endif /* at_lib_h */
