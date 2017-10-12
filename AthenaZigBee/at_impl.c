//
//  at_impl.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#include "at_impl.h"


T_DATA onVersionHandler(T_DATA args[]) {
    return RET_REPLY(AT_VER, "2017.10M");
};

T_DATA onMACHandler(T_DATA args[]) {
    return RET_REPLY(AT_MAC, "ABCDEF");
};
