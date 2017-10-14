//
//  main.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//
#include "util.h"
#include "at_lib.h"
#include "at_impl.h"

// 注册AT处理函数
void initATSystem() {
	registerAT(KEY_AT_R, onRebootHandler);
	registerAT(KEY_AT_Z, onResetHandler);
	registerAT(KEY_AT_VER, onVersionHandler);
	registerAT(KEY_AT_RSSI, onRSSIHandler);
	registerAT(KEY_AT_MAC, onMACHandler);
	registerAT(KEY_AT_UART, onUARTHandler);
	registerAT(KEY_AT_NWK, onNetworkAddHandler);
	registerAT(KEY_AT_CLEAR, onClearHandler);
	registerAT(KEY_AT_TYPE, onTypeHandler);
	registerAT(KEY_AT_STAT, onStatusHandler);
	registerAT(KEY_AT_PAN, onPanIdHandler);
	registerAT(KEY_AT_CH, onChannelHandler);
	registerAT(KEY_AT_GPIO, onGPIOHandler);
	registerAT(KEY_AT_RGPIO, onRGPIOHandler);
	registerAT(KEY_AT_IODIR, onIODIRHandler);
	registerAT(KEY_AT_RIODIR, onRIODIRHandler);
	registerAT(KEY_AT_INT, onINTHandler);
	registerAT(KEY_AT_RINT, onRINTHandler);
	registerAT(KEY_AT_PWM, onPWMHandler);
	registerAT(KEY_AT_RPWM, onRPWMHandler);
	registerAT(KEY_AT_ADC, onADCHandler);
	registerAT(KEYAT_RADC, onRADCMHandler);
	registerAT(KEY_AT_CNF_PWM, onConfPWMHandler);
}

// 处理AT命令
void processATRequest(pchar at) {
	unsigned int len = checkAT(at);
	if (len > 0) {
		struct atRequest req = parseAT(len, at);
		if (ERR_CODE_NONE == req.err && req.index >= 0) {
			_log(handleAT(req));
		}
		else {
			_log((ERR_CODE_ARGUMENT == req.err) ? (RET_ERR_ARGS) : (RET_ERR_UNSUP));
		}
	}
	else {
		_log(RET_ERR_UNSUP);
	}
}

int main(int argc, const char * argv[]) {
	initATSystem();
	processATRequest("AT+R");
	processATRequest("AT+VER=");
	processATRequest("AT+PWM=12");
	processATRequest("AT+GPIO=34");
	processATRequest("AT+INT=56,EN,DU");
	processATRequest("AT+RINT=78,DIS,DU,A1");
	processATRequest("AT+CNF_PWM=90");
	getchar();
	return 0;
}
