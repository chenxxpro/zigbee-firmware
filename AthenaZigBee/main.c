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

int main(int argc, const char * argv[]) {
    _log("########\n");
    T_DATA at = "AT+VER";
    
    // 注册AT处理函数
    registerAT(AT_VER, onVersionHandler);
    registerAT(AT_MAC, onMACHandler);
    
    // 处理AT命令
    if (checkAT(at)) {
        _log(handleAT(at));
    }else{
        _log(RET_ERR_UNK);
    }
    return 0;
}
