
#include <WinSock2.h>
#include <ws2tcpip.h>

#include <cstdint>

#pragma comment (lib, "ws2_32.lib")
//#include <websocket.h>

#define WSAERROR(FunctionNullonSucces) \
	if(FunctionNullonSucces != 0)	\
	{								\
	printf("ERROR: "#FunctionNullonSucces);\
	printf(":\nCode:  %i\n\n", WSAGetLastError());\
	}
// AF_UNSPEC

namespace Tool
{
	namespace Network
	{
		class Socket;
		class UdpConnection;
		class TcpConnection;
		class BluetoothConnection;
		class IP;
		class IPv4;
		class IPv6;
		class TcpSocketv4;
		class TcpSocketv6;
		class UdpSocketv4;
		class UdpSocketv6;
		
		class InvalidSocket;

	}
}