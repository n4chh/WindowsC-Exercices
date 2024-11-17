#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define COL_RESET "\033[0m"
#define COL_RED "\033[31m"
#define COL_GREEN "\033[32m"
#define COL_YELLOW "\033[33m"
#define COL_BLUE "\033[34m"
#define COL_MAGENTA "\033[35m"
#define COL_CYAN "\033[36m"
#define COL_BOLD "\033[1m"
// Esta macro nos permite gestionar los errores de la llamada a una función.
// La macro solo se ejecutará correctamente si callback es una función y si se han
// proporcionado los parámetros que necesita la propia función para ejecutarse
// correctamente. En caso contrario, el compilador debería de mostrar un fallo.
#define ERROR_HANDLER(sCode, funcName,callback, ...) \
	if (sCode != 0) {\
		printLog(ERR,"Bad status sCode: %d\n", sCode);\
		printLog(WARNING,"Catched at function: "COL_BOLD"%s"COL_RESET"\n", funcName);\
		if (callback != NULL) callback(__VA_ARGS__);\
		exit(1);\
	}

typedef enum{
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	SUCCESS,
	ERR,
	LOGLEVELS
} logLevel;

# ifndef LOGLEVEL
static logLevel LLEVEL = INFO;
# else
static logLevel LLEVEL = LOGLEVEL;
# endif


static char *LOGPREFIX[LOGLEVELS] = {
	[TRACE] = "["COL_CYAN "."COL_RESET"]",
	[DEBUG] = "["COL_CYAN COL_BOLD"#"COL_RESET"]",
	[INFO] = "["COL_BLUE COL_BOLD"*"COL_RESET"]",
	[WARNING] = "["COL_YELLOW COL_BOLD"-"COL_RESET"]",
	[SUCCESS] = "["COL_GREEN COL_BOLD"+"COL_RESET"]",
	[ERR] = "["COL_RED COL_BOLD"!"COL_RESET"]",
};

void printLog(const logLevel l, const char *format, ...);
#endif
