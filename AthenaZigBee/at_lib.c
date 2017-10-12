//
//  at_lib.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#include "at_lib.h"

const int checkAT(T_DATA at) {
    return strlen(at) > 3 &&
            'A' == *(at + 0) &&
            'T' == *(at + 1) &&
            '+' == *(at + 2);
}


void regAT(T_DATA act) {
    
}
