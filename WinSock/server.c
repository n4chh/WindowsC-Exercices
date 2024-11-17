#include <WinSock2.h>
#include <WS2tcpip.h>
#include "utils.h"
#define PORT "4444"

void	initWinSockApp(WSADATA* wsaData);
void	cleanUp(SOCKET* s, struct addrinfo* data);

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
	// https://learn.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
	iResult = getaddrinfo(NULL, PORT, &hints, &addrData);
	ERROR_HANDLER(iResult, getaddrinfo, WSACleanup);
	ListenSocket = socket(addrData->ai_family, addrData->ai_socktype, addrData->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
		ERROR_HANDLER(WSAGetLastError(),"socket", cleanUp, &ListenSocket, addrData);
	iResult = bind(ListenSocket, addrData->ai_addr, addrData->ai_addrlen);
	if (iResult == SOCKET_ERROR)
		ERROR_HANDLER(WSAGetLastError(),"bind", cleanUp,&ListenSocket,addrData);
	freeaddrinfo(addrData);
	ERROR_HANDLER(1, "bind", cleanUp, &ListenSocket, addrData);
	// Escuchar en el socket
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
		ERROR_HANDLER(WSAGetLastError(),"listen",cleanUp,&ListenSocket,NULL);
	// Recibir la conexión
	/*iResult = recv(ListenSocket );*/

	return 0;
}

// Siempre que se hace uso de la api WinSock, es necesario inicializarla
// https://learn.microsoft.com/en-us/windows/win32/winsock/initializing-winsock
void initWinSockApp(WSADATA*	wsaData) {
	int iResult;
	printf("["COL_YELLOW"-"COL_RESET"] ");
	printf("Initiliazing socket\n");
	iResult = WSAStartup(MAKEWORD(2,2), wsaData);
	// WSAStartup devuelve el codigo de error deseado, no es necesario llamar
	// a WSAGetLastError. 
	// https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsastartup
 	ERROR_HANDLER(iResult, __func__, WSACleanup);
}

void cleanUp(SOCKET* s, struct addrinfo* data) {
	if (s != NULL && *s != INVALID_SOCKET) {
		closesocket(*s);	
	}
	if (data != NULL) {
		freeaddrinfo(data);
	}
	WSACleanup();
}
