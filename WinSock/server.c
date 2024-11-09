#include <WinSock2.h>
#include <WS2tcpip.h>
#include "utils.h"

void	initWinSockApp(WSADATA* wsaData);

// WSA -> Windows Socket Application
int main(void) {
	WSADATA wsaData; // WinSockApp Data
	SOCKET ListenSocket = INVALID_SOCKET; // Socket
			
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
	errorHandler(1, __func__, (void (*)(void))hello_world);
	errorHandler(iResult, __func__, (void (*)(void))WSACleanup);
}
