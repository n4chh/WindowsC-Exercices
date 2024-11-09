#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include "colors.h"

#pragma comment(lib, "ws2_32")

void	initWinSockApp(WSADATA* wsaData);
void	errorHandler(int sCode, const char *fName);

// WSA -> Windows Socket Application
int main(void) {
	WSADATA wsaData; // WinSockApp Data
	printf("["COL_BOLD COL_BLUE"*"COL_RESET"] ");
	printf("Starting Program\n");
	initWinSockApp(&wsaData);
	return 0;
}

// Siempre que se hace uso de la api WinSock, es necesario inicializarla
void initWinSockApp(WSADATA*	wsaData) {
	int iResult;
	printf("["COL_YELLOW"-"COL_RESET"] ");
	printf("Initiliazing socket\n");
	iResult = WSAStartup(MAKEWORD(2,2), wsaData);
	errorHandler(iResult, __func__);
}


void errorHandler(int sCode, const char *fName) {
	if (sCode != 0)
	{
		printf("["COL_BOLD COL_RED"*"COL_RESET"] ");
		printf("Bad status code: %d\n", sCode);
		printf("["COL_RED"!"COL_RESET"] ");
		printf("Catched at function: "COL_BOLD"%s"COL_RESET, fName);
		printf("\n");
		exit(1);
	}
	return ;
}
