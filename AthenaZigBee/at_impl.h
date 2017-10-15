#ifndef at_impl_h
#define at_impl_h

#include "at_lib.h"

// Reboot
void onRebootHandler(const struct atRequest * req, char* output);

// Reset
void onResetHandler(const struct atRequest * req, char* output);

// Version
void onVersionHandler(const struct atRequest * req, char* output);

// RSSI
void onRSSIHandler(const struct atRequest * req, char* output);

// MAC
void onMACHandler(const struct atRequest * req, char* output);

// UART
void onUARTHandler(const struct atRequest * req, char* output);

// Network
void onNetworkAddHandler(const struct atRequest * req, char* output);

// Clear
void onClearHandler(const struct atRequest * req, char* output);

// Device Type
void onDeviceTypeHandler(const struct atRequest * req, char* output);

// Device Status
void onDeviceStateHandler(const struct atRequest * req, char* output);

// PANID
void onPanIdHandler(const struct atRequest * req, char* output);

// Channel
void onChannelHandler(const struct atRequest * req, char* output);

// GPIO
void onGPIOHandler(const struct atRequest * req, char* output);

// RGPIO
void onRGPIOHandler(const struct atRequest * req, char* output);

// IO Pull
void onIOPullHandler(const struct atRequest * req, char* output);

// IODIR
void onIODIRHandler(const struct atRequest * req, char* output);

// Remote IODIR
void onRIODIRHandler(const struct atRequest * req, char* output);

// Config PWM
void onINTTriggerHandler(const struct atRequest * req, char* output);

// INT
void onINTHandler(const struct atRequest * req, char* output);

// Remote INT
void onRINTHandler(const struct atRequest * req, char* output);

// Config PWM
void onConfPWMHandler(const struct atRequest * req, char* output);

// PWM
void onPWMHandler(const struct atRequest * req, char* output);

// Remote PWM
void onRPWMHandler(const struct atRequest * req, char* output);

// ADC
void onADCHandler(const struct atRequest * req, char* output);

// Remote ADC
void onRADCMHandler(const struct atRequest * req, char* output);

#endif /* at_impl_h */
