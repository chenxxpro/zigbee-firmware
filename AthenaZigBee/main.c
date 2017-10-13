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
    registerAT(INDEX_AT_VER, onVersionHandler);
    registerAT(INDEX_AT_MAC, onMACHandler);
}

// 处理AT命令
void processATRequest(T_DATA at) {
    unsigned int len = checkAT(at);
    if (len > 0) {
        struct T_AT_REQ req = parseAT(len, at);
        if (req.index >= 0) {
            _log(handleAT(req));
        }else{
            _log(RET_ERR_UNK);
        }
    }else{
        _log(RET_ERR_UNK);
    }
}

int main(int argc, const char * argv[]) {
    _log("########\n");
    initATSystem();
    T_DATA at = "AT+VER";
    processATRequest(at);
    return 0;
}
