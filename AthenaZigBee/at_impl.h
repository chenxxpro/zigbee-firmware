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


pchar onRebootHandler(struct atRequest req);

pchar onResetHandler(struct atRequest req);

pchar onVersionHandler(struct atRequest req);

pchar onRSSIHandler(struct atRequest req);

pchar onMACHandler(struct atRequest req);

pchar onUARTHandler(struct atRequest req);

pchar onNetworkAddHandler(struct atRequest req);

pchar onClearHandler(struct atRequest req);

pchar onTypeHandler(struct atRequest req);

pchar onStatusHandler(struct atRequest req);

pchar onPanIdHandler(struct atRequest req);

pchar onChannelHandler(struct atRequest req);

pchar onGPIOHandler(struct atRequest req);

pchar onRGPIOHandler(struct atRequest req);

pchar onIODIRHandler(struct atRequest req);

pchar onRIODIRHandler(struct atRequest req);

pchar onINTHandler(struct atRequest req);

pchar onRINTHandler(struct atRequest req);

pchar onPWMHandler(struct atRequest req);

pchar onRPWMHandler(struct atRequest req);

pchar onADCHandler(struct atRequest req);

pchar onRADCMHandler(struct atRequest req);

pchar onConfPWMHandler(struct atRequest req);

#endif /* at_impl_h */
