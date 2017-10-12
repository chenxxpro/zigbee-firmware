//
//  at_lib.h
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#ifndef at_lib_h
#define at_lib_h

typedef const char* T_DATA;

// 检查AT命令
const int checkAT(T_DATA at);

// 注册AT命令和回调函数
void regAT(T_DATA act);

#endif /* at_lib_h */
