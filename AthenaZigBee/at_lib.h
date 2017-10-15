#ifndef at_lib_h
#define at_lib_h

#include "types.h"


#define RET_ERRMSG_UNSUP		"+ERR=AT_UNSUPPORT\n"
#define RET_ERRMSG_ARGS			"+ERR=ARGUMENTS\n"
#define RET_NAMED_UNSUP(X)		"+ERR=AT_UNSUPPORT,"X"\n"
#define RET_NAMED_OK(AT)		"+"AT"=OK\n"
#define RET_NAMED_ARG(AT)		"+"AT"=ERR,ARGUMENTS\n"
#define RET_NAMED_RTIME(AT)		"+"AT"=ERR,RUNTIME\n"
#define RET_NAMED_REPLY(AT,RET)	"+"AT"="RET"\n"

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

#define NAME_AT_IOPULL	"IOPULL"
#define NAME_AT_IODIR   "IODIR"
#define NAME_AT_RIODIR  "RIODIR"

#define NAME_AT_INTTRI	"INTTRI"
#define NAME_AT_INT     "INT"
#define NAME_AT_RINT    "RINT"

#define NAME_AT_CNF_PWM "CNF_PWM"
#define NAME_AT_PWM     "PWM"
#define NAME_AT_RPWM    "RPWM"

#define NAME_AT_ADC     "ADC"
#define NAME_AT_RADC    "RADC"

#define KEY_AT_R		0
#define KEY_AT_Z		1
#define KEY_AT_VER		2
#define KEY_AT_RSSI		3
#define KEY_AT_MAC		4
#define KEY_AT_UART		5
#define KEY_AT_TYPE		6
#define KEY_AT_NWK		7
#define KEY_AT_CLEAR	8
#define KEY_AT_STAT		9
#define KEY_AT_PAN		10
#define KEY_AT_CH		11
#define KEY_AT_GPIO		12
#define KEY_AT_RGPIO	13
#define KEY_AT_IODIR	14
#define KEY_AT_RIODIR	15
#define KEY_AT_INT		16
#define KEY_AT_RINT		17
#define KEY_AT_PWM		18
#define KEY_AT_RPWM		19
#define KEY_AT_ADC		20
#define KEY_AT_RADC		21
#define KEY_AT_CNF_PWM	22
#define KEY_AT_INTTRI	23
#define KEY_AT_IOPULL	24

// Count Of AT Commands
#define AT_CMD_COUNT    25

// AT+
#define AT_CMD_IPREFIX  3
// e.g: AT+R
#define AT_CMD_MIN_LEN  4

// AT+[LOOOOOOONGCMD]=
// MAX: AT+RINTTRI
// MAX: AT_CNF_PWM
#define AT_CMD_FIELD_MAX_LEN	7
#define AT_CMD_FIELD_BUF_SIZE	AT_CMD_FIELD_MAX_LEN + 1

// Result Codes
#define RET_CODE_SUCCESS	0
#define RET_CODE_UNSUPPORT	1
#define RET_CODE_ARGUMENT	2

// Invalid argument
#define AT_INVALID_ARG		-1
#define AT_INVALID_PIN		255

// AT Command result buff size
// +RGPIO=(0:0:AB)x21 + (,)x20
#define AT_BUFF_RESPONSE_SIZE		7 + 6 * AT_CMD_COUNT + 1 * (AT_CMD_COUNT - 1)

// All AT request char size.
// AT+RINTTRI=1:2,EN,PD,FC:AA:14:E1:E2:CB
#define AT_REQUEST_MAX_LEN		sizeof("AT+RINTTRI=1:2,EN,PD,FC:AA:14:E1:E2:CB")
#define AT_BUFF_REQUEST_SIZE	AT_REQUEST_MAX_LEN + 1

#define ARG_C_STATE1	'E' // State Disabled
#define ARG_C_STATE0	'D' // State Enabled
#define ARG_C_TTL1		'H' // TTL High
#define ARG_C_TTL0		'L' // TTL Low
#define ARG_C_DIR1		'O' // Dir Output
#define ARG_C_DIR0		'I' // Dir Input
#define ARG_C_PULL1		'D' // Pull Down
#define ARG_C_PULL0		'U' // Pull Up
#define ARG_C_MODE1		'N' // Mode None
#define ARG_C_MODE0		'P' // Mode Pull

#define ARG_N_DIRIN		0  // Dir Input

#define _isSetArg(A)	(A != AT_INVALID_ARG)

// AT request command struct
struct atRequest {
	// Error code	
    uchar status;

	// AT command Index
	uint index;

	// Pin Group
	uchar group;

	// Pin number
	uchar pin;

	// Arg 0
	uint arg0;

	// Arg 1
	uchar arg1;

	// Arg 2
	uchar arg2;
};

// AT command handler
typedef void (*atHandler)(const struct atRequest * req, char* output);

// check if AT Command is valid
uint checkAT(pchar at);

// parseAT command to request struct
void parseAT(struct atRequest * req, const uint len, pchar command);

// register AT command handler
void registerAT(const uint index, const atHandler handler);

// handle AT request
void handleAT(const struct atRequest * req, char* output);

#endif /* at_lib_h */
