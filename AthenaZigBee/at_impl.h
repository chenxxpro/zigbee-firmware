#ifndef at_impl_h
#define at_impl_h

#include "at_lib.h"

// Reboot
const uint onRebootHandler(const struct atRequest * req, char* output);

// Reset
const uint onResetHandler(const struct atRequest * req, char* output);

// Version
const uint onVersionHandler(const struct atRequest * req, char* output);

// RSSI
const uint onRSSIHandler(const struct atRequest * req, char* output);

// MAC
const uint onMACHandler(const struct atRequest * req, char* output);

// UART
const uint onUARTHandler(const struct atRequest * req, char* output);

// Network
const uint onNetworkAddHandler(const struct atRequest * req, char* output);

// Clear
const uint onClearHandler(const struct atRequest * req, char* output);

// Device Type
const uint onTypeHandler(const struct atRequest * req, char* output);

// Device Status
const uint onStatusHandler(const struct atRequest * req, char* output);

// PANID
const uint onPanIdHandler(const struct atRequest * req, char* output);

// Channel
const uint onChannelHandler(const struct atRequest * req, char* output);

// GPIO
const uint onGPIOHandler(const struct atRequest * req, char* output);

// RGPIO
const uint onRGPIOHandler(const struct atRequest * req, char* output);

// IODIR
const uint onIODIRHandler(const struct atRequest * req, char* output);

// Remote IODIR
const uint onRIODIRHandler(const struct atRequest * req, char* output);

// INT
const uint onINTHandler(const struct atRequest * req, char* output);

// Remote INT
const uint onRINTHandler(const struct atRequest * req, char* output);

// PWM
const uint onPWMHandler(const struct atRequest * req, char* output);

// Remote PWM
const uint onRPWMHandler(const struct atRequest * req, char* output);

// ADC
const uint onADCHandler(const struct atRequest * req, char* output);

// Remote ADC
const uint onRADCMHandler(const struct atRequest * req, char* output);

// Config PWM
const uint onConfPWMHandler(const struct atRequest * req, char* output);

#endif /* at_impl_h */
