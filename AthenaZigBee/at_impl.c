//
//  at_impl.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#include "at_impl.h"


T_DATA onVersionHandler(struct T_AT_REQ req) {
    return RET_REPLY(NAME_AT_VER, "2017.10M");
};

T_DATA onMACHandler(struct T_AT_REQ req) {
    return RET_REPLY(NAME_AT_MAC, "ABCDEF");
};
