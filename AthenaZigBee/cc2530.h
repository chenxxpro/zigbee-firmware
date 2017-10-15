#ifndef cc2530_h
#define cc2530_h

#include "env.h"

// WIN32 DEBUG
#ifdef _PC_ENV

// Pin Group
extern unsigned char WIN32_P0 = 0;
extern unsigned char WIN32_P1 = 0;
extern unsigned char WIN32_P2 = 0;
#define P0 WIN32_P0
#define P1 WIN32_P1
#define P2 WIN32_P2

// Pin IO Dir
extern unsigned char WIN32_P0DIR = 0;
extern unsigned char WIN32_P1DIR = 0;
extern unsigned char WIN32_P2DIR = 0;
#define P0DIR WIN32_P0DIR
#define P1DIR WIN32_P1DIR
#define P2DIR WIN32_P2DIR

// Pin Pull State
extern unsigned char WIN32_P0INP = 0;
extern unsigned char WIN32_P1INP = 0;
extern unsigned char WIN32_P2INP = 0;
#define P0INP WIN32_P0INP
#define P1INP WIN32_P1INP
#define P2INP WIN32_P2INP

// Pin Intertuptors
extern unsigned char WIN32_IEN0 = 0;
extern unsigned char WIN32_IEN1 = 0;
extern unsigned char WIN32_IEN2 = 0;
#define IEN0 WIN32_IEN0
#define IEN1 WIN32_IEN1
#define IEN2 WIN32_IEN2
extern unsigned char WIN32_P0IEN = 0;
extern unsigned char WIN32_P1IEN = 0;
extern unsigned char WIN32_P2IEN = 0;
#define P0IEN WIN32_P0IEN
#define P1IEN WIN32_P1IEN
#define P2IEN WIN32_P2IEN
extern unsigned char WIN32_PICTL = 0;
#define PICTL WIN32_PICTL

extern unsigned char WIN32_PERCFG = 0;
#define PERCFG WIN32_PERCFG
extern unsigned char WIN32_P0SEL = 0;
#define P0SEL WIN32_P0SEL
extern unsigned char WIN32_U0CSR = 0;
#define U0CSR WIN32_U0CSR
extern unsigned char WIN32_U0GCR = 0;
#define U0GCR WIN32_U0GCR
extern unsigned char WIN32_U0BAUD = 0;
#define U0BAUD WIN32_U0BAUD
extern unsigned char WIN32_UTX0IF = 0;
#define UTX0IF WIN32_UTX0IF
extern unsigned char WIN32_U0DBUF = 0;
#define U0DBUF WIN32_U0DBUF

extern unsigned char WIN32_CLKCONCMD = 0;
#define CLKCONCMD WIN32_CLKCONCMD
extern unsigned char WIN32_CLKCONSTA = 0;
#define CLKCONSTA WIN32_CLKCONSTA
#else

#include <ioCC2530.h>

#endif // !_WIN32

#endif /* cc2530_h */
