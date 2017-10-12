//
//  main.c
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#include "util.h"
#include "at_lib.h"


int main(int argc, const char * argv[]) {
    _log("########!\n");

    if (checkAT("AT+VER")) {
        _log("IS AT\n");
    }else{
        _log("NOT AT\n");
    }
    return 0;
}
