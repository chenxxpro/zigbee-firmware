//
//  at_lib.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include "at_lib.h"

#define AT_IDX 3
#define HANDLER_SIZE 2

struct E_ACTION {
    T_DATA act;
    AT_HANDLER handler;
} E_ACTION;

struct E_ACTION _HANDLERS[HANDLER_SIZE];

const int checkAT(T_DATA at) {
    return strlen(at) > AT_IDX &&
            'A' == *(at + 0) &&
            'T' == *(at + 1) &&
            '+' == *(at + 2);
}

void registerAT(T_DATA act, AT_HANDLER handler) {
    int registered = 0;
    for (int i = 0; i < HANDLER_SIZE; i++) {
        struct E_ACTION item = _HANDLERS[i];
        if (NULL == item.act) {
            item.act = act;
            item.handler = handler;
            registered = 1;
            break;
        }
    }
    if (registered == 0) {
        printf("!!! Handler not registered !!!\n");
    }
}


T_DATA handleAT(T_DATA at) {
    T_DATA act = (at + AT_IDX);
    AT_HANDLER handler = NULL;
    for (int i = 0; i < HANDLER_SIZE; i++) {
        struct E_ACTION item = _HANDLERS[i];
        if (strcmp(act, item.act) == 0) {
            handler = item.handler;
            break;
        }
    }
    if (NULL != handler) {
        return RET_OK("VER");
    }else{
        return RET_ERR_UNK;
    }
    
}
