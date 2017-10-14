#ifndef at_impl_h
#define at_impl_h

#include "at_lib.h"

// Reboot
pchar onRebootHandler(struct atRequest req);

// Reset
pchar onResetHandler(struct atRequest req);

// Version
pchar onVersionHandler(struct atRequest req);

// RSSI
pchar onRSSIHandler(struct atRequest req);

// MAC
pchar onMACHandler(struct atRequest req);

// UART
pchar onUARTHandler(struct atRequest req);

// Network
pchar onNetworkAddHandler(struct atRequest req);

// Clear
pchar onClearHandler(struct atRequest req);

// Device Type
pchar onTypeHandler(struct atRequest req);

// Device Status
pchar onStatusHandler(struct atRequest req);

// PANID
pchar onPanIdHandler(struct atRequest req);

// Channel
pchar onChannelHandler(struct atRequest req);

// GPIO
pchar onGPIOHandler(struct atRequest req);

// RGPIO
pchar onRGPIOHandler(struct atRequest req);

// IODIR
pchar onIODIRHandler(struct atRequest req);

// Remote IODIR
pchar onRIODIRHandler(struct atRequest req);

// INT
pchar onINTHandler(struct atRequest req);

// Remote INT
pchar onRINTHandler(struct atRequest req);

// PWM
pchar onPWMHandler(struct atRequest req);

// Remote PWM
pchar onRPWMHandler(struct atRequest req);

// ADC
pchar onADCHandler(struct atRequest req);

// Remote ADC
pchar onRADCMHandler(struct atRequest req);

// Config PWM
pchar onConfPWMHandler(struct atRequest req);

#endif /* at_impl_h */
