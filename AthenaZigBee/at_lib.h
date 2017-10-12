//
//  at_lib.h
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#ifndef at_lib_h
#define at_lib_h

// 检查命令是否为AT指令
unsigned checkAT(const char* at) {
    return 'A' == *(at + 0) &&
        'T' == *(at + 1) &&
        '+' == *(at + 2);
}

// 注册AT命令和回调函数
void regAT(const char* act);

#endif /* at_lib_h */
