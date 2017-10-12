//
//  util.h
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#ifndef util_h
#define util_h

#include <stdio.h>

void _log(const char* message) {
    printf("%s", message);
}

void sendData(const char* data) {
    printf("%s", data);
}

#endif /* util_h */
