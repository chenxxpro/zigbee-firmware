#include <string.h>
#include "bits.h"
#include "halpin.h"
#include "at_lib.h"

// Check Pin Group range
#define _checkGroupRange(G)	('0' <= G && G <= '2')
// Check Pin Range
#define _checkPinRange(P)	('0' <= P && P <= '7')
// Check Pin & Group: PinGroup2: Pin0-4
#define _checkGrpPinRange(G, P) ( '2' == G ? ('0' <= P && P <= '4') : 1)

// Handlers
atHandler _HANDLERS[AT_CMD_SIZE] = { NULL };

// parse AT command name to index
const int parseargs_idx(pchar name) {
	if (0 == strcmp(name, NAME_AT_R)) { return KEY_AT_R; }
	else if (0 == strcmp(name, NAME_AT_Z)) { return KEY_AT_Z; }
	else if (0 == strcmp(name, NAME_AT_VER)) { return KEY_AT_VER; }
	else if (0 == strcmp(name, NAME_AT_RSSI)) { return KEY_AT_RSSI; }
	else if (0 == strcmp(name, NAME_AT_MAC)) { return KEY_AT_MAC; }
	else if (0 == strcmp(name, NAME_AT_UART)) { return KEY_AT_UART; }
	else if (0 == strcmp(name, NAME_AT_TYPE)) { return KEY_AT_TYPE; }
	else if (0 == strcmp(name, NAME_AT_NWK)) { return KEY_AT_NWK; }
	else if (0 == strcmp(name, NAME_AT_CLEAR)) { return KEY_AT_CLEAR; }
	else if (0 == strcmp(name, NAME_AT_STAT)) { return KEY_AT_STAT; }
	else if (0 == strcmp(name, NAME_AT_PAN)) { return KEY_AT_PAN; }
	else if (0 == strcmp(name, NAME_AT_CH)) { return KEY_AT_CH; }
	else if (0 == strcmp(name, NAME_AT_GPIO)) { return KEY_AT_GPIO; }
	else if (0 == strcmp(name, NAME_AT_RGPIO)) { return KEY_AT_RGPIO; }
	else if (0 == strcmp(name, NAME_AT_IOPULL)) { return KEY_AT_IOPULL; }
	else if (0 == strcmp(name, NAME_AT_IODIR)) { return KEY_AT_IODIR; }
	else if (0 == strcmp(name, NAME_AT_RIODIR)) { return KEY_AT_RIODIR; }
	else if (0 == strcmp(name, NAME_AT_INTTRI)) { return KEY_AT_INTTRI; }
	else if (0 == strcmp(name, NAME_AT_INT)) { return KEY_AT_INT; }
	else if (0 == strcmp(name, NAME_AT_RINT)) { return KEY_AT_RINT; }
	else if (0 == strcmp(name, NAME_AT_CNF_PWM)) { return KEY_AT_CNF_PWM; }
	else if (0 == strcmp(name, NAME_AT_PWM)) { return KEY_AT_PWM; }
	else if (0 == strcmp(name, NAME_AT_RPWM)) { return KEY_AT_RPWM; }
	else if (0 == strcmp(name, NAME_AT_ADC)) { return KEY_AT_ADC; }
	else if (0 == strcmp(name, NAME_AT_RADC)) { return KEYAT_RADC; }
	else { return -1; }
}

// parse args of bool/int
const int parseargs_argx(pchar arg) {
	if (0 == strcmp(arg, "1") ||
		0 == strcmp(arg, "SE") || // State Enable
		0 == strcmp(arg, "TH") || // TTL High
		0 == strcmp(arg, "DO") || // Dir Out
		0 == strcmp(arg, "PD") || // Pull Down
		0 == strcmp(arg, "MN")) { // Mode None
		return 1;
	}
	else if (0 == strcmp(arg, "0") ||
		0 == strcmp(arg, "SD") ||	// State Disable
		0 == strcmp(arg, "TL") ||	// TTL Low
		0 == strcmp(arg, "DI") ||	// Dir In
		0 == strcmp(arg, "PU") ||	// Pull Up
		0 == strcmp(arg, "MP")) {	// Mode Pull
		return 0;
	}
	else {
		return *arg;
	}
}

// check if AT index without args.
const int hasargs_none(const int ati) {
	return (ati == KEY_AT_R ||
		ati == KEY_AT_Z ||
		ati == KEY_AT_VER ||
		ati == KEY_AT_MAC ||
		ati == KEY_AT_RSSI);
}

//////////////

const uint checkAT(pchar at) {
	const uint len = (uint)strlen(at);
	if (len >= AT_CMD_MIN_LEN &&
		'A' == *(at + 0) &&
		'T' == *(at + 1) &&
		'+' == *(at + 2)) {
		return len;
	}
	else {
		return 0;
	}
}


const struct atRequest parseAT(const uint length, pchar command) {
	const uint idxEnd = length - 1; // Pointer to command end index;
	uint flags = 0; // Flags of bits
	uint dataHead = AT_CMD_IPREFIX; // Current data pointer
	uint dataOffset = 0; // Pointer for read start
	uint idxHead = AT_CMD_IPREFIX; // Current read pointer
	uint separator = 0; // Flag of separator: "=" / ","

	struct atRequest req;
	req.error = RET_CODE_SUCCESS;
	req.index = 0;
	req.group = PIN_INVALID;
	req.pin = PIN_INVALID;
	req.arg0 = AT_ARG_INVALID;
	req.arg1 = AT_ARG_INVALID;
	req.arg2 = AT_ARG_INVALID;

	// AT+[CMD]=[PIN|ARG0],[ARG1],[ARG2],...
	while (idxHead <= idxEnd) {
		const char token = *(command + idxHead);
		dataOffset++;
		separator = '=' == token || ',' == token;
		if (separator || idxHead == idxEnd) {
			if (dataOffset > AT_SEG_MAX_LEN) { // Check command name length			
                req.error = RET_CODE_ARGUMENT;
				break;
			}
			char buf[AT_SEG_BUF_LEN] = { 0 };
			strncpy(buf, (command + dataHead), (dataOffset - separator));
			dataHead += dataOffset;
			dataOffset = 0;
			// Command Index, BIT0
			if (! IS_BIT1_OF(flags, 0)) {
				SETBIT1_OF(flags, BITM_0);
				req.index = parseargs_idx(buf);
			}
			// Arguments
			else if (! hasargs_none(req.index)) {
				// Pin, BIT1
				if (! IS_BIT1_OF(flags, 1)) {
					SETBIT1_OF(flags, BITM_1);
					// Only Group
					const uint bl = strlen(buf);
					if (1 == bl && _checkGroupRange(buf[0])) {
						req.group = _nctoi(buf[0]);
					}
					// GroupPin: [GROUP : NUM]
					else if (3 == bl && ':' == buf[1] 
							&& _checkGroupRange(buf[0])
							&& _checkPinRange(buf[2])
							&& _checkGrpPinRange(buf[0], buf[2])) {
						req.group = _nctoi(buf[0]);
						req.pin = _nctoi(buf[2]);
					}else {
						req.error = RET_CODE_ARGUMENT;
						break;
					}
				}
				else {
					// Arg0, BIT2
					if (!IS_BIT1_OF(flags, 2)) {
						SETBIT1_OF(flags, BITM_2);
						req.arg0 = parseargs_argx(buf);
					}// Arg1, BIT3
					else if (!IS_BIT1_OF(flags, 3)) {
						SETBIT1_OF(flags, BITM_4);
						req.arg1 = parseargs_argx(buf);
					}// Arg2, BIT4
					else if (!IS_BIT1_OF(flags, 4)) {
						SETBIT1_OF(flags, BITM_4);
						req.arg2 = parseargs_argx(buf);
					}
					else {
						req.error = RET_CODE_ARGUMENT;
						break;
					}
				}
			}
		}
		idxHead++;
	}
	return req;
}

void registerAT(const uint index, const atHandler handler) {
	_HANDLERS[index] = handler;
}

const uint handleAT(const struct atRequest * req, char* output) {
	const atHandler handler = (_HANDLERS[(*req).index]);
	if (NULL == handler) {
		strcpy(output, RET_ERR_UNSUP);
		return RET_CODE_UNSUPPORT;
	}
	else {
		return handler(req, output);
	}
}
