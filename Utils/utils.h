#include <stdio.h>
#include <stdlib.h>

#define COL_RESET "\033[0m"
#define COL_RED "\033[31m"
#define COL_GREEN "\033[32m"
#define COL_YELLOW "\033[33m"
#define COL_BLUE "\033[34m"
#define COL_BOLD "\033[1m"

void	errorHandler(int sCode, const char *fName, void (*callback)(void));
