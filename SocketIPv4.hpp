#ifndef SOCKETIPV4_HPP_INCLUDED
#define SOCKETIPV4_HPP_INCLUDED

#include "Network.hpp"
#include "Socket.hpp"
#include "IPv4.hpp"


namespace Tool
{
	namespace Network
	{
		class SocketIPv4 : public Socket
		{
		public:
			SocketIPv4(SOCKET sock, Type socketType, Protocol protocol);
			SocketIPv4(SOCKET sock, SOCKADDR_IN clientAddress, Type socketType, Protocol protocol);
			SocketIPv4(Socket::Type socketType, Socket::Protocol protocol);
			SocketIPv4(Socket sock);
			~SocketIPv4();
			SocketIPv4 Accept(bool blocking);
			void Bind(IPv4 ip, uint16_t port);
			void Bind(SOCKADDR_IN address);
			int Connect(IPv4 ip, uint16_t port);
			int Connect(SOCKADDR_IN address);
		};
	}
}

#endif//SOCKETIPV4_HPP_INCLUDED
