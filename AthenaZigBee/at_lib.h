//
//  at_lib.h
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#ifndef at_lib_h
#define at_lib_h

#define RET_ERR_UNK "+ERR=UNK\n"

#define RET_OK(AT) "+"AT"=OK\n"
#define RET_ERR_ARG(AT) "+"AT"=ERR,ARG\n"
#define RET_ERR_EXE(AT) "+"AT"=ERR,EXE\n"

#define RET_REPLY(AT,RET) "+"AT"="RET"\n"

#define AT_VER "VER"
#define AT_MAC "MAC"

// 数据类型
typedef const char* T_DATA;

// AT命令处理函数
typedef T_DATA (*AT_HANDLER)(T_DATA args[]);
#define DEF_AT_HANDLER(name) T_DATA name(T_DATA args[])

// 检查AT命令
const int checkAT(T_DATA at);

// 注册AT命令和回调函数
void registerAT(T_DATA act, AT_HANDLER handler);

// 处理AT命令
T_DATA handleAT(T_DATA at);

#endif /* at_lib_h */
