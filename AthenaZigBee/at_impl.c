//
//  at_impl.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#include "at_impl.h"

pchar onRebootHandler(struct atRequest req) {
    return RET_OK(NAME_AT_R);
}

pchar onResetHandler(struct atRequest req) {
    return RET_OK(NAME_AT_Z);
}

pchar onVersionHandler(struct atRequest req) {
    return RET_OK(NAME_AT_VER);
}

pchar onRSSIHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RSSI);
}

pchar onMACHandler(struct atRequest req) {
    return RET_OK(NAME_AT_MAC);
}

pchar onUARTHandler(struct atRequest req) {
    return RET_OK(NAME_AT_UART);
}

pchar onNetworkAddHandler(struct atRequest req) {
    return RET_OK(NAME_AT_NWK);
}

pchar onClearHandler(struct atRequest req) {
    return RET_OK(NAME_AT_CLEAR);
}

pchar onTypeHandler(struct atRequest req) {
    return RET_OK(NAME_AT_TYPE);
}

pchar onStatusHandler(struct atRequest req) {
    return RET_OK(NAME_AT_STAT);
}

pchar onPanIdHandler(struct atRequest req) {
    return RET_OK(NAME_AT_PAN);
}

pchar onChannelHandler(struct atRequest req) {
    return RET_OK(NAME_AT_CH);
}

pchar onGPIOHandler(struct atRequest req) {
    return RET_OK(NAME_AT_GPIO);
}

pchar onRGPIOHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RGPIO);
}

pchar onIODIRHandler(struct atRequest req) {
    return RET_OK(NAME_AT_IODIR);
}

pchar onRIODIRHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RIODIR);
}

pchar onINTHandler(struct atRequest req) {
    return RET_OK(NAME_AT_INT);
}

pchar onRINTHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RINT);
}

pchar onPWMHandler(struct atRequest req) {
    return RET_OK(NAME_AT_PWM);
}

pchar onRPWMHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RPWM);
}

pchar onADCHandler(struct atRequest req) {
    return RET_OK(NAME_AT_ADC);
}

pchar onRADCMHandler(struct atRequest req) {
    return RET_OK(NAME_AT_RADC);
}

pchar onConfPWMHandler(struct atRequest req) {
    return RET_OK(NAME_AT_CNF_PWM);
}
