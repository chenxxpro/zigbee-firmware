//
//  at_lib.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//
#include <string.h>
#include "at_lib.h"

AT_HANDLER _HANDLERS[AT_CMD_SIZE];

// 检查AT指令
const unsigned int checkAT(T_DATA at) {
    const unsigned int len = (unsigned int) strlen(at);
    if (len > AT_CMD_MIN_LEN &&
        'A' == *(at + 0) &&
        'T' == *(at + 1) &&
        '+' == *(at + 2)) {
        return len;
    }else{
        return 0;
    }
}

// 解析AT命令
const struct T_AT_REQ parseAT(const unsigned int len, T_DATA command) {
    struct T_AT_REQ req;
    req.index = -1;
    req.args = 0;
    return req;
}

// 注册处理函数
void registerAT(int ATIndex, const AT_HANDLER handler) {
    _HANDLERS[ATIndex] = handler;
}

// 处理AT请求
T_DATA handleAT(const struct T_AT_REQ req) {
    return (_HANDLERS[req.index])(req);
}
