//
//  at_impl.h
//  AthenaZigBee
//
//  Created by YoojiaChen on 2017/10/12.
//  Copyright © 2017年 yoojia. All rights reserved.
//

#ifndef at_impl_h
#define at_impl_h

#include "at_lib.h"


T_DATA onRebootHandler(struct T_AT_REQ req);

T_DATA onResetHandler(struct T_AT_REQ req);

T_DATA onVersionHandler(struct T_AT_REQ req);

T_DATA onRSSIHandler(struct T_AT_REQ req);

T_DATA onMACHandler(struct T_AT_REQ req);

T_DATA onUARTHandler(struct T_AT_REQ req);

T_DATA onNetworkAddHandler(struct T_AT_REQ req);

T_DATA onClearHandler(struct T_AT_REQ req);

T_DATA onTypeHandler(struct T_AT_REQ req);

T_DATA onStatusHandler(struct T_AT_REQ req);

T_DATA onPanIdHandler(struct T_AT_REQ req);

T_DATA onChannelHandler(struct T_AT_REQ req);

T_DATA onGPIOHandler(struct T_AT_REQ req);

T_DATA onRGPIOHandler(struct T_AT_REQ req);

T_DATA onIODIRHandler(struct T_AT_REQ req);

T_DATA onRIODIRHandler(struct T_AT_REQ req);

T_DATA onINTHandler(struct T_AT_REQ req);

T_DATA onRINTHandler(struct T_AT_REQ req);

T_DATA onPWMHandler(struct T_AT_REQ req);

T_DATA onRPWMHandler(struct T_AT_REQ req);

T_DATA onADCHandler(struct T_AT_REQ req);

T_DATA onRADCMHandler(struct T_AT_REQ req);

T_DATA onConfPWMHandler(struct T_AT_REQ req);

#endif /* at_impl_h */
