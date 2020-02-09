#include "Client.h"
#include "Packet.h"
#include "Datagram.h"
#include "Address6.h"
#include "Address4.h"
#include "WSA.h"
namespace Tool
{
	namespace Network
	{
		Client::Client(Address6 remoteAddress, u16 localPort): data(0)
		{
			this->wsa = new WSA();
			sockaddr_in6 localAddress;
			u32 blockmode = 1;
			u32 outcount;
			int length = sizeof(localAddress);
			localAddress.sin6_addr = in6addr_any;
			localAddress.sin6_family = AF_INET6;
			localAddress.sin6_port = htons(localPort);
			localAddress.sin6_flowinfo = 0;
			localAddress.sin6_scope_id = 0;

			sock = WSASocket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP, 0, 0, 0);
			WSAERROR(sock == INVALID_SOCKET)
			WSAIoctl( sock, FIONBIO, &blockmode, sizeof(u32), &blockmode, sizeof(u32), &outcount, 0, 0);
			WSAERROR(bind( sock, (const sockaddr*) &localAddress, length))
			WSAERROR(WSAConnect(sock,(sockaddr*) &remoteAddress.Tosockaddr(), sizeof(sockaddr_in6), 0, 0, 0, 0))
		}
		Client::Client(Address4 remoteAddress, u16 localPort): data(0)
		{
			this->wsa = new WSA();
			sockaddr_in localAddress;
			u32 blockmode = 1;
			u32 outcount;
			int length = sizeof(localAddress);
			localAddress.sin_addr.S_un.S_addr = 0;
			localAddress.sin_family = AF_INET;
			localAddress.sin_port = htons(localPort);

			sock = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, 0, 0, 0);
			WSAERROR(sock == INVALID_SOCKET)
			WSAIoctl( sock, FIONBIO, &blockmode, sizeof(u32), &blockmode, sizeof(u32), &outcount, 0, 0);
			WSAERROR(bind( sock, (const sockaddr*) &localAddress, length))
			WSAERROR(WSAConnect(sock,(sockaddr*) &remoteAddress.Tosockaddr(), sizeof(sockaddr_in), 0, 0, 0, 0))
		}
		Client::Client(Address4 remoteAddress, Address4 localAddress): data(0)
		{
			this->wsa = new WSA();
			u32 blockmode = 1;
			u32 outcount;
			int length = sizeof(localAddress);

			sock = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, 0, 0, 0);
			WSAERROR(sock == INVALID_SOCKET)
			WSAIoctl( sock, FIONBIO, &blockmode, sizeof(u32), &blockmode, sizeof(u32), &outcount, 0, 0);
			WSAERROR(bind( sock, (const sockaddr*) &localAddress, length))
			WSAERROR(WSAConnect(sock,(sockaddr*) &remoteAddress.Tosockaddr(), sizeof(sockaddr_in), 0, 0, 0, 0))
		}
		Client::Client(Address6 remoteAddress, Address6 localAddress): data(0)
		{
			this->wsa = new WSA();
			u32 blockmode = 1;
			u32 outcount;
			int length = sizeof(localAddress);

			sock = WSASocket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP, 0, 0, 0);
			WSAERROR(sock == INVALID_SOCKET)
			WSAIoctl( sock, FIONBIO, &blockmode, sizeof(u32), &blockmode, sizeof(u32), &outcount, 0, 0);
			WSAERROR(bind( sock, (const sockaddr*) &localAddress, length))
			WSAERROR(WSAConnect(sock,(sockaddr*) &remoteAddress.Tosockaddr(), sizeof(sockaddr_in6), 0, 0, 0, 0))
		}

		Client::~Client(void)
		{
			closesocket(this->sock);
			delete data;
			delete this->wsa;
		}

		void Client::Send(Packet* packet)
		{
			Datagram data;
			u16 iD = packet->GetID();
			data.Write<w16>(iD);
			send(packet->Get(&data));
		}

		u32 Client::send(Datagram* data)
		{
			WSABUF buffer = { data->Size(), (CHAR*)data->Data()};
			u32 sentBytes;
			WSAERROR(WSASend(sock, &buffer, 1, &sentBytes, 0, 0, 0))
			return sentBytes;
		}

		int Client::receive(WSABUF* buffer)
		{
			int result;
			DWORD flags =  0;
			length = sizeof(sockaddr_in6);
			buffer->buf = (CHAR*) new w8[65536];
			buffer->len = 65536;
			result = WSARecvFrom(sock, buffer, 1, &(buffer->len), &flags, (sockaddr*) &this->lastReceiveAddress, &length, 0, 0);
			return result;
		}

		Address6 Client::GetLastReceiveAddress(void)
		{
			return Address6(lastReceiveAddress);
		}

		u16 Client::Checkout(void)
		{
			WSABUF buf;
			receive(&buf);
			data = new Datagram((w8*)buf.buf, buf.len);
			delete[] buf.buf;
			buf.len = 0;
			return data->Read<u16>();
		}

		Packet* Client::Receive(Packet* outPacket)
		{
			outPacket->Set(data);
			return outPacket;
		}
	}
}
