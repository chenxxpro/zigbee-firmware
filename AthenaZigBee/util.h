#ifndef util_h
#define util_h

#ifdef _WIN32

#include <stdio.h>

#else

const int printf(const char* const message, ...) {
	return 0;
}


#endif // !_WIN32

#endif /* util_h */
