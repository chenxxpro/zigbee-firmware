//
//  main.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "at_lib.h"
#include "at_impl.h"
#include "bits.h"

// 注册AT处理函数
void initATSystem() {
    registerAT(INDEX_AT_R, onRebootHandler);
    registerAT(INDEX_AT_Z, onResetHandler);
    registerAT(INDEX_AT_VER, onVersionHandler);
    registerAT(INDEX_AT_RSSI, onRSSIHandler);
    registerAT(INDEX_AT_MAC, onMACHandler);
    registerAT(INDEX_AT_UART, onUARTHandler);
    registerAT(INDEX_AT_NWK, onNetworkAddHandler);
    registerAT(INDEX_AT_CLEAR, onClearHandler);
    registerAT(INDEX_AT_TYPE, onTypeHandler);
    registerAT(INDEX_AT_STAT, onStatusHandler);
    registerAT(INDEX_AT_PAN, onPanIdHandler);
    registerAT(INDEX_AT_CH, onChannelHandler);
    registerAT(INDEX_AT_GPIO, onGPIOHandler);
    registerAT(INDEX_AT_RGPIO, onRGPIOHandler);
    registerAT(INDEX_AT_IODIR, onIODIRHandler);
    registerAT(INDEX_AT_RIODIR, onRIODIRHandler);
    registerAT(INDEX_AT_INT, onINTHandler);
    registerAT(INDEX_AT_RINT, onRINTHandler);
    registerAT(INDEX_AT_PWM, onPWMHandler);
    registerAT(INDEX_AT_RPWM, onRPWMHandler);
    registerAT(INDEX_AT_ADC, onADCHandler);
    registerAT(INDEX_AT_RADC, onRADCMHandler);
    registerAT(INDEX_AT_CNF_PWM, onConfPWMHandler);
}

// 处理AT命令
void processATRequest(T_DATA at) {
    unsigned int len = checkAT(at);
    if (len > 0) {
        struct T_AT_REQ req = parseAT(len, at);
        if (req.index >= 0) {
            _log(handleAT(req));
        }else{
            _log(RET_ERR_UNSUP);
        }
    }else{
        _log(RET_ERR_UNSUP);
    }
}

int main(int argc, const char * argv[]) {
    initATSystem();
    processATRequest("AT+R");
    processATRequest("AT+VER=");
    processATRequest("AT+PWM=12");
    processATRequest("AT+GPIO=45");
    processATRequest("AT+INT=45,EN,DU");
    processATRequest("AT+CNF_PWM=45");
    return 0;
}
