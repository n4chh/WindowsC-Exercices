#include "utils.h"


void printLog(const logLevel l, const char *format, ...) {

	va_list argptr;
	

	if (l < LLEVEL || l >= LOGLEVELS)	
		return;	
	va_start(argptr, format);
	printf("%s ", LOGPREFIX[l]);
	vprintf(format, argptr);
	va_end(argptr);
	
}
