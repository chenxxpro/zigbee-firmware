#ifndef at_impl_h
#define at_impl_h

#include "at_lib.h"

// Reboot
const uint onRebootHandler(struct atRequest * req, char* output);

// Reset
const uint onResetHandler(struct atRequest * req, char* output);

// Version
const uint onVersionHandler(struct atRequest * req, char* output);

// RSSI
const uint onRSSIHandler(struct atRequest * req, char* output);

// MAC
const uint onMACHandler(struct atRequest * req, char* output);

// UART
const uint onUARTHandler(struct atRequest * req, char* output);

// Network
const uint onNetworkAddHandler(struct atRequest * req, char* output);

// Clear
const uint onClearHandler(struct atRequest * req, char* output);

// Device Type
const uint onTypeHandler(struct atRequest * req, char* output);

// Device Status
const uint onStatusHandler(struct atRequest * req, char* output);

// PANID
const uint onPanIdHandler(struct atRequest * req, char* output);

// Channel
const uint onChannelHandler(struct atRequest * req, char* output);

// GPIO
const uint onGPIOHandler(struct atRequest * req, char* output);

// RGPIO
const uint onRGPIOHandler(struct atRequest * req, char* output);

// IODIR
const uint onIODIRHandler(struct atRequest * req, char* output);

// Remote IODIR
const uint onRIODIRHandler(struct atRequest * req, char* output);

// INT
const uint onINTHandler(struct atRequest * req, char* output);

// Remote INT
const uint onRINTHandler(struct atRequest * req, char* output);

// PWM
const uint onPWMHandler(struct atRequest * req, char* output);

// Remote PWM
const uint onRPWMHandler(struct atRequest * req, char* output);

// ADC
const uint onADCHandler(struct atRequest * req, char* output);

// Remote ADC
const uint onRADCMHandler(struct atRequest * req, char* output);

// Config PWM
const uint onConfPWMHandler(struct atRequest * req, char* output);

#endif /* at_impl_h */
