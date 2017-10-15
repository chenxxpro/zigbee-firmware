#ifndef util_h
#define util_h

#ifdef _WIN32

#include <stdio.h>

#else

int printf(const char* const message, ...) {
	return 0;
}


#endif // !_WIN32


void delay_ms(int xms) {
	unsigned int i, j;
	for (i = xms; i > 0; i--) for (j = 587; j > 0; j--);
}


#endif /* util_h */
