#include <WinSock2.h>
#include <WS2tcpip.h>
#include "utils.h"
#define PORT "4444"

void	initWinSockApp(WSADATA* wsaData);

// WSA -> Windows Socket Application
int main(void) {
	WSADATA wsaData; // WinSockApp Data
	SOCKET ListenSocket = INVALID_SOCKET; // Socket
	int    iResult;
			
	printf("["COL_BOLD COL_BLUE"*"COL_RESET"] ");
	printf("Starting Program\n");
	initWinSockApp(&wsaData);

	struct addrinfo *addrData =  NULL, *ptr = NULL, hints;
	/*memset(&hints, 0, sizeof(hints));*/
	/*ZeroMemory(&hints, sizeof(hints));*/
	hints = (struct addrinfo){0};

	// Los dos primeros parametros de getaddrinfo son strings del host (node) y puerto (service)
	// El puerto puede ser especificado como numero o como servicio, "http" es equivalente a "80"
	iResult = getaddrinfo(NULL, PORT, &hints, &addrData);
	errorHandler(iResult, __func__, (void (*)(void))WSACleanup);
	ListenSocket = socket(addrData->ai_family, addrData->ai_socktype, addrData->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		// Importante liberar el heap 
		freeaddrinfo(addrData);
		errorHandler(1,__func__, (void (*)(void))WSACleanup);
	}
	iResult = bind(ListenSocket, addrData->ai_addr, addrData->ai_addrlen);
	freeaddrinfo(addrData);
	errorHandler(1, "bind", (void (*)(void))WSACleanup);
	// Recibir la conexión

	return 0;
}

// Siempre que se hace uso de la api WinSock, es necesario inicializarla
void initWinSockApp(WSADATA*	wsaData) {
	int iResult;
	printf("["COL_YELLOW"-"COL_RESET"] ");
	printf("Initiliazing socket\n");
	iResult = WSAStartup(MAKEWORD(2,2), wsaData);
	errorHandler(iResult, __func__, (void (*)(void))WSACleanup);
}
