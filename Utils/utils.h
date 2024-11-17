#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define COL_RESET "\033[0m"
#define COL_RED "\033[31m"
#define COL_GREEN "\033[32m"
#define COL_YELLOW "\033[33m"
#define COL_BLUE "\033[34m"
#define COL_BOLD "\033[1m"
// Esta macro nos permite gestionar los errores de la llamada a una función.
// La macro solo se ejecutará correctamente si callback es una función y si se han
// proporcionado los parámetros que necesita la propia función para ejecutarse
// correctamente. En caso contrario, el compilador debería de mostrar un fallo.
#define ERROR_HANDLER(sCode, funcName,callback, ...) \
	if (sCode != 0) {\
		printf("["COL_BOLD COL_RED"*"COL_RESET"] ");\
		printf("Bad status sCode: %d\n", sCode);\
		printf("["COL_RED "!" COL_RESET"] ");\
		printf("Catched at function: "COL_BOLD"%s"COL_RESET, __func__);\
		printf("\n");\
		if (callback != NULL) callback(__VA_ARGS__);\
		exit(1);\
	}

void	errorHandler(int sCode, const char *fName, void (*callback)(void), ...);
