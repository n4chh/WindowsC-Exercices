#include "utils.h"


void errorHandler(int sCode, const char *fName, void (*callback)(void)) {
	if (sCode != 0)
	{
		printf("["COL_BOLD COL_RED"*"COL_RESET"] ");
		printf("Bad status code: %d\n", sCode);
		printf("["COL_RED"!"COL_RESET"] ");
		printf("Catched at function: "COL_BOLD"%s"COL_RESET, fName);
		printf("\n");
		if (callback != NULL)
			callback();
		exit(1);
	}
	return ;
}
