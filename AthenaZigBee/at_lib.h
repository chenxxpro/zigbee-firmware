//
//  at_lib.h
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#ifndef at_lib_h
#define at_lib_h

#define RET_ERR_UNSUP       "+ERR=AT_UNSUPPORT\n"
#define RET_OK(AT)          "+"AT"=OK\n"
#define RET_ERR_ARG(AT)     "+"AT"=ERR,ARGUMENTS\n"
#define RET_ERR_EXE(AT)     "+"AT"=ERR,RUNTIME\n"

#define RET_REPLY(AT,RET)   "+"AT"="RET"\n"

#define NAME_AT_R       "R"
#define NAME_AT_Z       "Z"
#define NAME_AT_VER     "VER"
#define NAME_AT_RSSI    "RSSI"
#define NAME_AT_MAC     "MAC"
#define NAME_AT_UART    "UART"
#define NAME_AT_TYPE    "TYPE"
#define NAME_AT_NWK     "NWK"
#define NAME_AT_CLEAR   "CLEAR"
#define NAME_AT_STAT    "STAT"
#define NAME_AT_PAN     "PAN"
#define NAME_AT_CH      "CH"
#define NAME_AT_GPIO    "GPIO"
#define NAME_AT_RGPIO   "RGPIO"
#define NAME_AT_IODIR   "IODIR"
#define NAME_AT_RIODIR  "RIODIR"
#define NAME_AT_INT     "INT"
#define NAME_AT_RINT    "RINT"
#define NAME_AT_PWM     "PWM"
#define NAME_AT_RPWM    "RPWM"
#define NAME_AT_ADC     "ADC"
#define NAME_AT_RADC    "RADC"
#define NAME_AT_CNF_PWM "CNF_PWM"

#define INDEX_AT_R       0
#define INDEX_AT_Z       1
#define INDEX_AT_VER     2
#define INDEX_AT_RSSI    3
#define INDEX_AT_MAC     4
#define INDEX_AT_UART    5
#define INDEX_AT_TYPE    6
#define INDEX_AT_NWK     7
#define INDEX_AT_CLEAR   8
#define INDEX_AT_STAT    9
#define INDEX_AT_PAN     10
#define INDEX_AT_CH      11
#define INDEX_AT_GPIO    12
#define INDEX_AT_RGPIO   13
#define INDEX_AT_IODIR   14
#define INDEX_AT_RIODIR  15
#define INDEX_AT_INT     16
#define INDEX_AT_RINT    17
#define INDEX_AT_PWM     18
#define INDEX_AT_RPWM    19
#define INDEX_AT_ADC     20
#define INDEX_AT_RADC    21
#define INDEX_AT_CNF_PWM 22

#define AT_CMD_SIZE     23

#define AT_CMD_IPREFIX  3
#define AT_CMD_MIN_LEN  4
#define AT_CMD_MAX_LEN  9


#define FLAGS_AT    0
#define FLAGS_PIN   1
#define FLAGS_EN    2

// 数据类型
typedef const char* T_DATA;
typedef const char* P_DATA;

// AT命令请求参数结构体
struct T_AT_REQ {
    
    // AT指令Index
    int index;
    
    // 目标引脚
    unsigned int pin;
    
    // 参数列表
    unsigned int arg0;
    
    unsigned int arg1;
    
    unsigned int arg2;
};

// AT命令处理函数
typedef P_DATA (*AT_HANDLER)(struct T_AT_REQ req);
#define DEF_AT_HANDLER(name) T_DATA name(T_AT_REQ req)

// 检查AT指令
const unsigned int checkAT(P_DATA at);

// 解释AT指令
const struct T_AT_REQ parseAT(const unsigned int len, P_DATA command);

// 注册AT命令和回调函数
void registerAT(int ATIndex, const AT_HANDLER handler);

// 处理AT命令
P_DATA handleAT(const struct T_AT_REQ req);

#endif /* at_lib_h */
