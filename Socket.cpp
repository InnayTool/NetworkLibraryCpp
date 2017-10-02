#include "Socket.hpp"
#include "IPv4.hpp"
#include <iostream>

namespace Tool {
	namespace Network{
		static WSADATA data;
		//Socket::Socket(Socket & socket) : 
		uint16_t addressSize(AddressFamily addressFamily)
		{
			switch (addressFamily)
			{
			case ipv4:
				return sizeof(SOCKADDR_IN);
				break;
			case ipv6:
				return sizeof(SOCKADDR_IN6);
				break;
			case irda:
				return sizeof(SOCKADDR_IRDA);
				break;
			default:
				return sizeof(SOCKADDR_STORAGE);
			}
		}


		Socket::Socket(SOCKET socket, AddressFamily addressFamily, Type socketType, Protocol protocol)
			: socket(socket), addressFamily(addressFamily), type(socketType), protocol(protocol),
				accepted(false), bound(false), listening(false)
		{
			
		}
		Socket::Socket(SOCKET socket, SOCKADDR_STORAGE clientAddress, Type socketType, Protocol protocol) 
			: socket(socket), address(clientAddress), type(socketType), protocol(protocol),
				accepted(true ), bound(false), listening(false)
		{
			addressFamily = (AddressFamily)clientAddress.ss_family;
		}
		Socket::Socket(AddressFamily addressFamily, Type socketType, Protocol protocol) 
			:addressFamily(addressFamily), type(socketType), protocol(protocol),
				accepted(false), bound(false), listening(false)
		{
			WSAStartup(MAKEWORD(2, 2), &data);
			socket = ::socket(addressFamily, socketType, protocol);
		}

		Socket Socket::Accept(bool blocking)
		{
			SOCKADDR_STORAGE acceptedAddress;
			int addrlen = sizeof(acceptedAddress);
			SOCKET sock;
			u_long param = !blocking;

			if (ioctlsocket(socket, FIONBIO, &param))
				throw "ioctl failed!";

			sock = accept(socket, (SOCKADDR*)&acceptedAddress, &addrlen);
			if (sock == INVALID_SOCKET)
				throw "Invalid socket!";

			return Socket(socket, acceptedAddress, type, protocol);
		}
		void Socket::Listen()
		{
			return Listen(SOMAXCONN);
		}
		void Socket::Listen(size_t backlog)
		{
			if (backlog > SOMAXCONN)
				throw std::out_of_range("Backlog is to big!");
			this->backlog = backlog;
			if (listen(this->socket, backlog))
				throw WSAGetLastError();
			listening = true;
		}
		void Socket::Bind(SOCKADDR* address)
		{
			this->address = *((SOCKADDR_STORAGE*)address);
			if (address->sa_family != this->addressFamily)
				throw std::invalid_argument("Address has the wrong Family!");
			if (bind(this->socket, address, addressSize(this->addressFamily)))
				throw WSAGetLastError();
			bound = true;
		}
		int Socket::Connect(SOCKADDR* address)
		{
			this->address = *((SOCKADDR_STORAGE*)address);
			if (address->sa_family != this->addressFamily)
				throw std::invalid_argument("Address has the wrong Family!");
			return connect(this->socket, address, addressSize(this->addressFamily));
		}

		std::vector<uint8_t> Socket::Recieve()
		{
			u_long n;
			int returnvalue;
			if (ioctlsocket(socket, FIONREAD, &n) == SOCKET_ERROR)
				throw -1;
			std::vector<uint8_t> result;
			result.resize(n);
			returnvalue = recv(socket, (char*)result.data(), 100, 0);
			if (returnvalue == -1)
				n = 0;
			else if (returnvalue < 1)
				throw returnvalue;
			result.resize(n);
			return result;

		}
		std::vector<uint8_t> Socket::Recieve(size_t n)
		{
			int returnvalue;
			std::vector<uint8_t> result;
			result.resize(n);
			returnvalue = recv(socket, (char*)result.data(), 100, 0);
			if (returnvalue == -1)
				n = 0;
			else if (returnvalue < 1)
				throw returnvalue;
			result.resize(n);
			return result;
		}
		int Socket::Send(std::vector<uint8_t> data)
		{
			return send(socket, (char*)data.data(), data.size(), 0);
		}

		bool Socket::IsPendingRead(uint32_t timeoutinmicrosec)
		{
			int selectresult;
			TIMEVAL tv;
			tv.tv_usec = timeoutinmicrosec;
			fd_set fs;
			fs.fd_array[0] = socket;
			fs.fd_count = 1;
			selectresult = select(0, &fs, 0, 0, &tv);
			if (selectresult > 0)
				return true;
			else if (selectresult < 0)
				throw WSAGetLastError();
			return false;
		}
		bool Socket::IsPendingWrite(uint32_t timeoutinmicrosec)
		{
			int selectresult;
			TIMEVAL tv;
			tv.tv_usec = timeoutinmicrosec;
			fd_set fs;
			fs.fd_array[0] = socket;
			fs.fd_count = 1;
			selectresult = select(0, 0, &fs, 0, &tv);
			if (selectresult > 0)
				return true;
			else if (selectresult < 0)
				throw WSAGetLastError();
			return false;
		}

		SOCKET Socket::GetSocket()
		{
			return this->socket;
		}

		Socket::~Socket()
		{
			closesocket(socket);
			WSACleanup();
		}

		AddressFamily Socket::GetaddressFamily()
		{
			return addressFamily;
		}
		Socket::Type Socket::GetType()
		{
			return type;
		}
		Socket::Protocol Socket::GetProtocol()
		{
			return protocol;
		}
		SOCKADDR_STORAGE Socket::GetAddress()
		{
			return address;
		}
		size_t Socket::GetBacklog()
		{
			return backlog;
		}

		bool Socket::HasAccepted()
		{
			return accepted;
		}
		bool Socket::IsBound()
		{
			return bound;
		}
		bool Socket::IsListening()
		{
			return listening;
		}

	}
}
