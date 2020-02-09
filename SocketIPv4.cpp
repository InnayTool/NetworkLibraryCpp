#include "SocketIPv4.hpp"
#include "IPv4.hpp"
#include <iostream>

namespace Tool {
	namespace Network{
		static WSADATA data;
		//Socket::Socket(Socket & socket) : 
		SOCKADDR toSockaddr(IPv4 ip, uint16_t port)
		{
			SOCKADDR_IN addr;
			addr.sin_addr = ip.possixaddress();
			addr.sin_family = ipv4;
			addr.sin_port = htons(port);
			return *(SOCKADDR*)&addr;
		}

		SocketIPv4::SocketIPv4(SOCKET sock, Type socketType, Protocol protocol) 
			: Socket(sock, ipv4, socketType, protocol){}
		SocketIPv4::SocketIPv4(SOCKET sock, SOCKADDR_IN clientAddress, Type socketType, Protocol protocol)
			: Socket(sock, *((SOCKADDR_STORAGE*)&clientAddress), socketType, protocol)
		{
			if (clientAddress.sin_family != ipv4)
				throw std::invalid_argument("Address has the wrong Family!");
		}
		SocketIPv4::SocketIPv4(Type socketType, Protocol protocol) 
			: Socket(ipv4, socketType, protocol){}
		SocketIPv4::SocketIPv4(Socket sock) : Socket(sock)
		{
			if(this->addressFamily != ipv4)
				throw std::invalid_argument("Address has the wrong Family!");
		}

		SocketIPv4::~SocketIPv4(){}

		SocketIPv4 SocketIPv4::Accept(bool blocking)
		{
			return SocketIPv4(Socket::Accept(blocking));
		}
		void SocketIPv4::Bind(IPv4 ip, uint16_t port)
		{
			SOCKADDR addr = toSockaddr(ip, port);
			return Socket::Bind(&addr);
		}

		void SocketIPv4::Bind(SOCKADDR_IN address)
		{
			return Socket::Bind((SOCKADDR*)&address);
		}
		int SocketIPv4::Connect(IPv4 ip, uint16_t port)
		{
			SOCKADDR addr = toSockaddr(ip, port);
			return Socket::Connect(&addr);
		}
		int SocketIPv4::Connect(SOCKADDR_IN address)
		{
			return Socket::Connect((SOCKADDR*)&address);
		}
	}
}

