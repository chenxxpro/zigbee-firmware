#ifndef util_h
#define util_h

#include "env.h"

#ifdef _PC_ENV

#include <stdio.h>

#else

int printf(const char* const message, ...) {
	return 0;
}


#endif // !_PC_ENV


void delay_ms(int xms) {
	unsigned int i, j;
	for (i = xms; i > 0; i--) for (j = 587; j > 0; j--);
}


#endif /* util_h */
