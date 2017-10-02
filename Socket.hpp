#include "Network.hpp"
#include <vector>
#include <AF_Irda.h>

namespace Tool
{
	namespace Network
	{
		enum AddressFamily
		{
			unspecified = AF_UNSPEC,
			ipv4 = AF_INET,
			ipv6 = AF_INET6,
			appletalk = AF_APPLETALK,
			irda = AF_IRDA,
			bluetooth = AF_BTH
		};
		
		class Socket
		{
		public:
			enum Type
			{
				stream = SOCK_STREAM,
				datagram = SOCK_DGRAM,
				raw = SOCK_RAW,
				reliablemessagedatagram = SOCK_RDM,
				sequencialpacket = SOCK_SEQPACKET
			};
			enum Protocol
			{
				icmp = IPPROTO_ICMP,
				igmp = IPPROTO_IGMP,
				bluetooth = 3/* BTHPROTO_RFCOMM*/,
				tcp = IPPROTO_TCP,
				udp = IPPROTO_UDP,
				icmpv6 = IPPROTO_ICMPV6,
				rm = IPPROTO_PGM
			};

			//Socket(Socket &  socket);
			Socket(SOCKET sock, AddressFamily addressFamily, Type socketType, Protocol protocol);
			Socket(SOCKET sock, SOCKADDR_STORAGE clientAddress, Type socketType, Protocol protocol);
			Socket(AddressFamily addressFamily, Type socketType, Protocol protocol);
			~Socket();

			Socket Accept(bool blocking);
			void Listen();
			void Listen(size_t backlog);
			void Bind(SOCKADDR* address);
			
			//int Bind(IPv4 ip, uint16_t port, uint32_t scopeid = 0);
			//int Connect(IPv4 ip, uint16_t port, uint32_t scopeid = 0);
			int Connect(SOCKADDR* address);

			std::vector<uint8_t> Recieve();
			std::vector<uint8_t> Recieve(size_t n);

			int Send(std::vector<uint8_t> data);

			bool IsPendingRead(uint32_t timeoutinmicrosec);
			bool IsPendingWrite(uint32_t timeoutinmicrosec);
			
			AddressFamily GetaddressFamily();
			Type GetType();
			Protocol GetProtocol();
			SOCKET GetSocket();
			SOCKADDR_STORAGE GetAddress();
			size_t GetBacklog();

			bool HasAccepted();
			bool IsBound();
			bool IsListening();

		protected:
			AddressFamily addressFamily;
			Type type;
			Protocol protocol;
			SOCKET socket;
			SOCKADDR_STORAGE address;
			bool bound;
			bool listening;
			bool accepted;
			size_t backlog;


		};
	} 
}