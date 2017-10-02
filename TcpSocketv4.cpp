#include "TcpSocketv4.hpp"
#include "IPv4.hpp"

namespace Tool
{
	namespace Network
	{
		static WSADATA data;
		TcpSocketv4::TcpSocketv4()
		{
			WSAStartup(MAKEWORD(2, 2), &data);
			sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		}
		TcpSocketv4::TcpSocketv4(SOCKET socket)
		{
			sock = socket;
			//TODO: getsockopt(sock, )
		}
		TcpSocketv4 TcpSocketv4::Accept(bool blocking)
		{
			int addrlen = sizeof(remoteAddress);
			SOCKET sock;
			u_long param = !blocking;
			ioctlsocket(this->sock, FIONBIO, &param);
			sock = accept(this->sock, &remoteAddress, &addrlen);
			return TcpSocketv4(sock);
		}
		int TcpSocketv4::Listen(int backLog)
		{
			return listen(this->sock, backLog);
		}
		int TcpSocketv4::Bind(IPv4 ip, uint16_t port)
		{
			SOCKADDR_IN addr;
			addr.sin_addr = ip.possixaddress();
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			return bind(this->sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
		}
		int TcpSocketv4::Connect(IPv4 ip, uint16_t port)
		{

			SOCKADDR_IN addr;
			addr.sin_addr = ip.possixaddress();
			addr.sin_family = AF_INET;
			addr.sin_port = port;
			return connect(this->sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
		}

		SOCKET TcpSocketv4::Sock() const
		{
			return this->sock;
		}
	}
}