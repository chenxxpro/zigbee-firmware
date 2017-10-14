//
//  at_lib.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//
#include <string.h>
#include <stdio.h>
#include "bits.h"
#include "at_lib.h"
#include "hal_pin.h"

// 字符串解析成数字
const int _a2i(pchar str);

// AT指令处理器引用数组
atHandler _HANDLERS[AT_CMD_SIZE] = { NULL };

// 将指令转换为处理函数的Index
const int parseIndex(pchar name) {
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
	else if (0 == strcmp(name, NAME_AT_IODIR)) { return KEY_AT_IODIR; }
	else if (0 == strcmp(name, NAME_AT_RIODIR)) { return KEY_AT_RIODIR; }
	else if (0 == strcmp(name, NAME_AT_INT)) { return KEY_AT_INT; }
	else if (0 == strcmp(name, NAME_AT_RINT)) { return KEY_AT_RINT; }
	else if (0 == strcmp(name, NAME_AT_PWM)) { return KEY_AT_PWM; }
	else if (0 == strcmp(name, NAME_AT_RPWM)) { return KEY_AT_RPWM; }
	else if (0 == strcmp(name, NAME_AT_ADC)) { return KEY_AT_ADC; }
	else if (0 == strcmp(name, NAME_AT_RADC)) { return KEYAT_RADC; }
	else if (0 == strcmp(name, NAME_AT_CNF_PWM)) { return KEY_AT_CNF_PWM; }
	else { return -1; }
}

// 解析参数
const int parseargs_bool(pchar arg) {
	if (0 == strcmp(arg, "EN") ||
		0 == strcmp(arg, "H") ||
		0 == strcmp(arg, "DO") ||
		0 == strcmp(arg, "PD")) {
		return 1;
	}
	else if (0 == strcmp(arg, "DIS") ||
		0 == strcmp(arg, "L") ||
		0 == strcmp(arg, "DI") ||
		0 == strcmp(arg, "PU")) {
		return 0;
	}
	else {
		return -1;
	}
}

// AT指令是否不需要参数
const int args_none(const int ati) {
	return (ati == KEY_AT_R ||
		ati == KEY_AT_Z ||
		ati == KEY_AT_VER ||
		ati == KEY_AT_MAC ||
		ati == KEY_AT_RSSI);
}

// AT指令需要Pin参数
const int args_pin(const int ati) {
	return (ati == KEY_AT_GPIO ||
		ati == KEY_AT_RGPIO ||
		ati == KEY_AT_ADC ||
		ati == KEYAT_RADC ||
		ati == KEY_AT_PWM ||
		ati == KEY_AT_RPWM ||
		ati == KEY_AT_IODIR ||
		ati == KEY_AT_RIODIR ||
		ati == KEY_AT_INT ||
		ati == KEY_AT_RINT);
}

//////

// 检查AT指令
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

// 解析AT命令
const struct atRequest parseAT(const uint length, pchar command) {
	const uint idxEnd = length - 1; // 符号结束位置
	uint flags = 0; // 用处理标记参数处理情况的标志符号
	uint dataHead = AT_CMD_IPREFIX; // 读数据起始位 
	uint dataOffset = 0; // 读数据偏移位
	uint idxHead = AT_CMD_IPREFIX; // 当前已读到的字符指针位置
	uint separator = 0; // 分隔符标记位

	struct atRequest req;
	req.err = ERR_CODE_UNSUPPORT;
	req.index = 0;
	req.pin = PIN_NOP;
	req.arg0 = 0;
	req.arg1 = 0;
	req.arg2 = 0;

	// AT 命令格式：AT+[CMD]=[PIN],[ARG1],[ARG2],...
	while (idxHead <= idxEnd) {
		const char token = *(command + idxHead);
		dataOffset++;
		separator = '=' == token || ',' == token;
		if (separator || idxHead == idxEnd) {
			if (dataOffset > AT_SEG_MAX_LEN) { // 判断参数段长度
				req.index = ERR_CODE_ARGUMENT;
				break;
			}
			char buf[AT_SEG_BUF_LEN] = { 0 };
			strncpy(buf, (command + dataHead), (dataOffset - separator));
			dataHead += dataOffset;
			dataOffset = 0;
			printf("--> Args: %s\n", buf);
			// 解析Pin
			// 解释arg[0..2]
		}
		idxHead++;
	}
	/*for(int idxHead = AT_CMD_IPREFIX; idxHead < len; idxHead++) {
		const char token = *(command + idxHead);
		// TODO 检查AT指令字符：字母、数字、+、=
		// 第一阶段：解析AT指令，结束符为“=”或者字符结束。
		sOffset = ('=' == token);
		if(! IS_BIT1_OF0(flags) && _TOKEN_END) {
			char cmd[AT_CMD_MAX_LEN] = {0};
			tokenLen = _IDX2SIZE(idxHead) - rOffset;
			_BUF_COPY(cmd);
			MKBIT_1_OF(flags, BITM_0);
			rOffset += tokenLen;
			req.index = parseIndex(cmd);
			printf("--> AT.CMD: %s\n", cmd);
		} else
		// 第二阶段：解析参数
		if(IS_BIT1_OF0(flags) && !hasnoargs(req.index)){
			// PIN引脚编号
			if(hasargs_pin(req.index) && !IS_BIT1_OF1(flags)) {
				_COMMA_TOKEN;
				if(_TOKEN_END) {
					char pin[AT_ARG_MAX_LEN] = {0};
					tokenLen = _IDX2SIZE(idxHead) - rOffset;
					_BUF_COPY(pin);
					BIT1_OF1(flags);
					rOffset += tokenLen;
					req.pin = _a2i(pin);
					printf("## CMD.Pin: %d\n", req.pin);
				}
				_CHECK_END;
			} else {
				// Arg0
				if (! IS_BIT1_OF2(flags)) {
					_COMMA_TOKEN;
					if (_TOKEN_END) {
						char arg0[AT_ARG_BUF_LEN] = { 0 };
						tokenLen = _IDX2SIZE(idxHead) - rOffset;
						_BUF_COPY(arg0);
						BIT1_OF2(flags);
						rOffset += tokenLen;
						req.arg0 = parseArg(arg0);
						printf("## CMD.Arg0: %s\n", arg0);
					}
					_CHECK_END;
				}
				// Arg1
				else if (!IS_BIT1_OF3(flags)) {
					_COMMA_TOKEN;
					if (_TOKEN_END) {
						char arg1[AT_ARG_BUF_LEN] = { 0 };
						tokenLen = _IDX2SIZE(idxHead) - rOffset;
						_BUF_COPY(arg1);
						IS_BIT1_OF3(flags);
						rOffset += tokenLen;
						printf("## CMD.Arg1: %s\n", arg1);
					}
					_CHECK_END;
				}// Arg2
				else if (!IS_BIT1_OF4(flags)) {
					_COMMA_TOKEN;
					if (_TOKEN_END) {
						char arg2[AT_ARG_BUF_LEN] = { 0 };
						tokenLen = _IDX2SIZE(idxHead) - rOffset;
						_BUF_COPY(arg2);
						IS_BIT1_OF4(flags);
						rOffset += tokenLen;
						printf("## CMD.Arg2: %s\n", arg2);
					}
				}
			}

		}
	}
	*/
	return req;
}

// 注册处理函数
void registerAT(int index, atHandler handler) {
	_HANDLERS[index] = handler;
}

// 处理AT请求
pchar handleAT(const struct atRequest req) {
	const atHandler handler = (_HANDLERS[req.index]);
	if (NULL == handler) {
		return RET_ERR_UNSUP;
	}
	else {
		return handler(req);
	}
}

//////

const int _a2i(pchar str) {
	int value = 0;
	int flag = 1; //判断符号
	//跳过字符串前面的空格
	while (*str == ' ') {
		str++;
	}
	//第一个字符若是‘-’，说明可能是负数
	if (*str == '-') {
		flag = 0;
		str++;
	}
	//第一个字符若是‘+’，说明可能是正数
	else if (*str == '+') {
		flag = 1;
		str++;
	}//第一个字符若不是‘+’‘-’也不是数字字符，直接返回0
	else if (*str >= '9' || *str <= '0') {
		return 0;
	}
	//当遇到非数字字符或遇到‘/0’时，结束转化
	while (*str != '/0' && *str <= '9' && *str >= '0') {
		value = value * 10 + *str - '0'; //将数字字符转为对应的整形数
		str++;
	}
	//负数的情况
	if (flag == 0) {
		value = -value;
	}
	return value;
}
