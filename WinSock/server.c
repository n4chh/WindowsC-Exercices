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
			
	printLog(INFO, "Starting Program\n");
	initWinSockApp(&wsaData);

	struct addrinfo *addrData =  NULL, *ptr = NULL, hints;
	/*memset(&hints, 0, sizeof(hints));*/
	/*ZeroMemory(&hints, sizeof(hints));*/
	hints = (struct addrinfo){0};

	// Los dos primeros parametros de getaddrinfo son strings del host (node) y puerto (service)
	// El puerto puede ser especificado como numero o como servicio, "http" es equivalente a "80"
	// https://learn.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
	iResult = getaddrinfo(NULL, PORT, &hints, &addrData);
	if (iResult == SOCKET_ERROR)
		ERROR_HANDLER(WSAGetLastError(),"getaddrinfo", cleanUp, &ListenSocket, addrData);
	ListenSocket = socket(addrData->ai_family, addrData->ai_socktype, addrData->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
		ERROR_HANDLER(WSAGetLastError(),"socket", cleanUp, &ListenSocket, addrData);
	iResult = bind(ListenSocket, addrData->ai_addr, addrData->ai_addrlen);
	if (iResult == SOCKET_ERROR)
		ERROR_HANDLER(WSAGetLastError(),"bind", cleanUp,&ListenSocket,addrData);
	// la función freeaddrinfo solo libera memoria, pero el puntero pasado como 
	// argumento mantiene la dirección de la memoria que se ha liberado. Es decir es 
	// necesario igualarlo a NULL para evitar acceder a memoria liberada en un futuro.
	// https://learn.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-freeaddrinfo
	freeaddrinfo(addrData);
	addrData = NULL;
	ERROR_HANDLER(1, "bind", cleanUp, &ListenSocket, addrData);
	// Escuchar en el socket
	// Según la documentación de microsoft, la función listen es bloqueante.
	// Por tanto dicha función se mantendrá a la espera de un evento de red
	// como por ejemplo, una nueva conexión. Esto se puede utilizar para 
	// implementar en el programa principal un bucle que genere hilos, 
	// de modo que cada hilo es una petición nueva aceptada por el servidor.
	// https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen#remarks
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
	printLog(DEBUG,"Initiliazing socket\n");
	iResult = WSAStartup(MAKEWORD(2,2), wsaData);
 	ERROR_HANDLER(iResult, __func__, WSACleanup);
	// WSAStartup devuelve el codigo de error deseado, no es necesario llamar
	// a WSAGetLastError. 
	// https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsastartup
}

void cleanUp(SOCKET* s, struct addrinfo* data) {
	//TODO: Comprobar los datos para evitar liberar o cerrar valores indebidos.
	if (s != NULL && *s != INVALID_SOCKET) {
		closesocket(*s);	
	}
	if (data != NULL) {
		freeaddrinfo(data);
	}
	WSACleanup();
}
