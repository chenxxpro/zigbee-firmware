#ifndef cc2530_h
#define cc2530_h

// WIN32 DEBUG
#ifdef _WIN32

// Pin Group
extern int WIN32_P0 = 0;
extern int WIN32_P1 = 0;
extern int WIN32_P2 = 0;
#define P0 WIN32_P0
#define P1 WIN32_P1
#define P2 WIN32_P2

// Pin IO Dir
extern int WIN32_P0DIR = 0;
extern int WIN32_P1DIR = 0;
extern int WIN32_P2DIR = 0;
#define P0DIR WIN32_P0DIR
#define P1DIR WIN32_P1DIR
#define P2DIR WIN32_P2DIR

// Pin Pull State
extern int WIN32_P0INP = 0;
extern int WIN32_P1INP = 0;
extern int WIN32_P2INP = 0;
#define P0INP WIN32_P0INP
#define P1INP WIN32_P1INP
#define P2INP WIN32_P2INP

// Pin Intertuptors
extern int WIN32_IEN0 = 0;
extern int WIN32_IEN1 = 0;
extern int WIN32_IEN2 = 0;
#define IEN0 WIN32_IEN0
#define IEN1 WIN32_IEN1
#define IEN2 WIN32_IEN2
extern int WIN32_P0IEN = 0;
extern int WIN32_P1IEN = 0;
extern int WIN32_P2IEN = 0;
#define P0IEN WIN32_P0IEN
#define P1IEN WIN32_P1IEN
#define P2IEN WIN32_P2IEN
extern int WIN32_PICTL = 0;
#define PICTL WIN32_PICTL

#else

#include <ioCC2530.h>

#endif // !_WIN32

#endif /* cc2530_h */
