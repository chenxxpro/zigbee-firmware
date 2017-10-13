//
//  at_impl.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#include "at_impl.h"

T_DATA onRebootHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_R);
}

T_DATA onResetHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_Z);
}

T_DATA onVersionHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_VER);
}

T_DATA onRSSIHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_RSSI);
}

T_DATA onMACHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_MAC);
}

T_DATA onUARTHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_UART);
}

T_DATA onNetworkAddHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_NWK);
}

T_DATA onClearHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_CLEAR);
}

T_DATA onTypeHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_TYPE);
}

T_DATA onStatusHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_STAT);
}

T_DATA onPanIdHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_PAN);
}

T_DATA onChannelHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_CH);
}

T_DATA onGPIOHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_GPIO);
}

T_DATA onRGPIOHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_RGPIO);
}

T_DATA onIODIRHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_IODIR);
}

T_DATA onRIODIRHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_RIODIR);
}

T_DATA onINTHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_INT);
}

T_DATA onRINTHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_RINT);
}

T_DATA onPWMHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_PWM);
}

T_DATA onRPWMHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_RPWM);
}

T_DATA onADCHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_ADC);
}

T_DATA onRADCMHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_RADC);
}

T_DATA onConfPWMHandler(struct T_AT_REQ req) {
    return RET_OK(NAME_AT_CNF_PWM);
}
