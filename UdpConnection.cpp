#include "UdpConnection.hpp"
#include <ws2tcpip.h>
namespace Tool { namespace Network {

	static SOCKET sock;
	UdpConnection::UdpConnection(std::string address, int16_t localPort)
	{
		int32_t blockmode = 1;
		int32_t outcount;
		WSADATA data;
		sockaddr_in6 localAddress, remoteAddress;
		int length = sizeof(localAddress);
		WSAStartup(MAKEWORD(2, 2), &data);
		sock = WSASocket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP, 0, 0, 0);
		WSAERROR(sock == INVALID_SOCKET);
		WSAIoctl(sock, FIONBIO, &blockmode, sizeof(int32_t), &blockmode, sizeof(int32_t), (LPDWORD) &outcount, 0, 0);
		WSAERROR(bind(sock, (const sockaddr*)&localAddress, length))
		WSAERROR(WSAConnect(sock, (sockaddr*)&remoteAddress, sizeof(sockaddr_in6), 0, 0, 0, 0))

	}

	uint32_t Send(std::vector<int> & data)
	{
		WSABUF buffer = { data.size(), (CHAR*)data.data() };
		uint32_t sentBytes;
		WSASend(sock, &buffer, sizeof(int), (LPDWORD) &sentBytes, 0, 0, 0);
		return sentBytes;
	}

}
}