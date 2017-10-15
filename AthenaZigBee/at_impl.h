#ifndef at_impl_h
#define at_impl_h

#include "at_lib.h"

// Reboot
uint onRebootHandler(const struct atRequest * req, char* output);

// Reset
uint onResetHandler(const struct atRequest * req, char* output);

// Version
uint onVersionHandler(const struct atRequest * req, char* output);

// RSSI
uint onRSSIHandler(const struct atRequest * req, char* output);

// MAC
uint onMACHandler(const struct atRequest * req, char* output);

// UART
uint onUARTHandler(const struct atRequest * req, char* output);

// Network
uint onNetworkAddHandler(const struct atRequest * req, char* output);

// Clear
uint onClearHandler(const struct atRequest * req, char* output);

// Device Type
uint onDeviceTypeHandler(const struct atRequest * req, char* output);

// Device Status
uint onDeviceStateHandler(const struct atRequest * req, char* output);

// PANID
uint onPanIdHandler(const struct atRequest * req, char* output);

// Channel
uint onChannelHandler(const struct atRequest * req, char* output);

// GPIO
uint onGPIOHandler(const struct atRequest * req, char* output);

// RGPIO
uint onRGPIOHandler(const struct atRequest * req, char* output);

// IO Pull
uint onIOPullHandler(const struct atRequest * req, char* output);

// IODIR
uint onIODIRHandler(const struct atRequest * req, char* output);

// Remote IODIR
uint onRIODIRHandler(const struct atRequest * req, char* output);

// Config PWM
uint onINTTriggerHandler(const struct atRequest * req, char* output);

// INT
uint onINTHandler(const struct atRequest * req, char* output);

// Remote INT
uint onRINTHandler(const struct atRequest * req, char* output);

// Config PWM
uint onConfPWMHandler(const struct atRequest * req, char* output);

// PWM
uint onPWMHandler(const struct atRequest * req, char* output);

// Remote PWM
uint onRPWMHandler(const struct atRequest * req, char* output);

// ADC
uint onADCHandler(const struct atRequest * req, char* output);

// Remote ADC
uint onRADCMHandler(const struct atRequest * req, char* output);

#endif /* at_impl_h */
