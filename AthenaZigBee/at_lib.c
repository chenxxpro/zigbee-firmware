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

#define _IDX2SIZE(idx) idx + 1

// 字符串解析成数字
const int _a2i(const char *str);

// AT指令处理器引用数组
AT_HANDLER _HANDLERS[AT_CMD_SIZE] = {NULL};

// 将指令转换为处理函数的Index
const int parseIndex(const char name[]) {
    if(0 == strcmp(name, NAME_AT_R)){ return INDEX_AT_R; }
    else if(0 == strcmp(name, NAME_AT_Z)){ return INDEX_AT_Z; }
    else if(0 == strcmp(name, NAME_AT_VER)){ return INDEX_AT_VER; }
    else if(0 == strcmp(name, NAME_AT_RSSI)){ return INDEX_AT_RSSI; }
    else if(0 == strcmp(name, NAME_AT_MAC)){ return INDEX_AT_MAC; }
    else if(0 == strcmp(name, NAME_AT_UART)){ return INDEX_AT_UART; }
    else if(0 == strcmp(name, NAME_AT_TYPE)){ return INDEX_AT_TYPE; }
    else if(0 == strcmp(name, NAME_AT_NWK)){ return INDEX_AT_NWK; }
    else if(0 == strcmp(name, NAME_AT_CLEAR)){ return INDEX_AT_CLEAR; }
    else if(0 == strcmp(name, NAME_AT_STAT)){ return INDEX_AT_STAT; }
    else if(0 == strcmp(name, NAME_AT_PAN)){ return INDEX_AT_PAN; }
    else if(0 == strcmp(name, NAME_AT_CH)){ return INDEX_AT_CH; }
    else if(0 == strcmp(name, NAME_AT_GPIO)){ return INDEX_AT_GPIO; }
    else if(0 == strcmp(name, NAME_AT_RGPIO)){ return INDEX_AT_RGPIO; }
    else if(0 == strcmp(name, NAME_AT_IODIR)){ return INDEX_AT_IODIR; }
    else if(0 == strcmp(name, NAME_AT_RIODIR)){ return INDEX_AT_RIODIR; }
    else if(0 == strcmp(name, NAME_AT_INT)){ return INDEX_AT_INT; }
    else if(0 == strcmp(name, NAME_AT_RINT)){ return INDEX_AT_RINT; }
    else if(0 == strcmp(name, NAME_AT_PWM)){ return INDEX_AT_PWM; }
    else if(0 == strcmp(name, NAME_AT_RPWM)){ return INDEX_AT_RPWM; }
    else if(0 == strcmp(name, NAME_AT_ADC)){ return INDEX_AT_ADC; }
    else if(0 == strcmp(name, NAME_AT_RADC)){ return INDEX_AT_RADC; }
    else {
        return -1;
    }
}

// AT指令是否存在参数
const int hasnoargs(const int ati) {
    return (ati == INDEX_AT_R   ||
            ati == INDEX_AT_Z   ||
            ati == INDEX_AT_VER ||
            ati == INDEX_AT_MAC ||
            ati == INDEX_AT_RSSI);
}

// AT指令是否有Pin参数
const int hasargs_pin(const int ati) {
    return (ati == INDEX_AT_GPIO    ||
            ati == INDEX_AT_RGPIO   ||
            ati == INDEX_AT_ADC     ||
            ati == INDEX_AT_RADC    ||
            ati == INDEX_AT_PWM     ||
            ati == INDEX_AT_RPWM    ||
            ati == INDEX_AT_IODIR   ||
            ati == INDEX_AT_RIODIR  ||
            ati == INDEX_AT_INT     ||
            ati == INDEX_AT_RINT);
}

// 检查AT指令
const unsigned int checkAT(P_DATA at) {
    const unsigned int len = (unsigned int) strlen(at);
    if (len >= AT_CMD_MIN_LEN &&
        'A' == *(at + 0) &&
        'T' == *(at + 1) &&
        '+' == *(at + 2)) {
        return len;
    }else{
        return 0;
    }
}

// 解析AT命令
const struct T_AT_REQ parseAT(const unsigned int len, P_DATA command) {
    const unsigned int idxEnd = len - 1; // 符号结束位置
    // 0-CMD; 1-PIN;
    unsigned int flags = 0; // 用处理标记参数处理情况的标志符号
    unsigned int rOffset = AT_CMD_IPREFIX; // 当前读取数据有位置
    unsigned int sOffset = 0; // 分隔符号的偏移位置
    unsigned int tokenLen = 0; // 当前参数长度
    
    struct T_AT_REQ req;
    req.index = -1;
    req.pin = PIN_NOP;
    req.args = 0;
    
    // AT 命令格式：AT+[CMD]=[PIN],[ARG1],[ARG2],...
    // 直接跳过前缀来读取字符串内容
    for(int idxHead = AT_CMD_IPREFIX; idxHead < len; idxHead++) {
        const char token = *(command + idxHead);
        // TODO 检查AT指令字符：字母、数字、+、=
        // 第一阶段：解析AT指令，结束符为“=”或者字符结束。
        sOffset = ('=' == token);
        if(! IS_BIT0_IS_1(flags) &&
           (idxHead == idxEnd || 1 == sOffset)) {
            char cmd[AT_CMD_MAX_LEN] = {0};
            // AT+R
            tokenLen = _IDX2SIZE(idxHead) - rOffset;
            strncpy(cmd, command + rOffset, tokenLen - sOffset);
            SET_BIT0_TO_1(flags);
            rOffset += tokenLen;
            req.index = parseIndex(cmd);
            printf("--> AT.CMD: %s\n", cmd);
        } else
        // 第二阶段：解析参数
        if(IS_BIT0_IS_1(flags) && !hasnoargs(req.index)){
            // PIN引脚编号
            if(hasargs_pin(req.index) && !IS_BIT1_IS_1(flags)) {
                sOffset = (',' == token);
                if((idxHead == idxEnd || 1 == sOffset)) {
                    char pin[3] = {0};
                    tokenLen = _IDX2SIZE(idxHead) - rOffset;
                    strncpy(pin, command + rOffset, tokenLen - sOffset);
                    SET_BIT1_TO_1(flags);
                    rOffset += tokenLen;
                    req.pin = _a2i(pin);
                    printf("## CMD.Pin: %d\n", req.pin);
                }
            }
        }
    }
    return req;
}

// 注册处理函数
void registerAT(int ATIndex, const AT_HANDLER handler) {
    _HANDLERS[ATIndex] = handler;
}

// 处理AT请求
P_DATA handleAT(const struct T_AT_REQ req) {
    const AT_HANDLER handler = (_HANDLERS[req.index]);
    if(NULL == handler) {
        return RET_ERR_UNSUP;
    }else{
        return handler(req);
    }
}

//////

const int _a2i(const char *str) {
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
