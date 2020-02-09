#include "INCLUDE.H"


#define WSAERROR(FunctionNullonSucces) \
	if(FunctionNullonSucces != 0)	\
	{								\
		printf("ERROR: "#FunctionNullonSucces);\
		printf(":\nCode:  %i\n\n", WSAGetLastError());\
	}
class Tool::Network::Client
{
public:
	Client(Address6 remoteAddress, u16 localPort);
	Client(Address4 remoteAddress, u16 localPort);
	Client(Address6 remoteAddress, Address6 localAddress);
	Client(Address4 remoteAddress, Address4 localAddress);
	~Client(void);

	void Send(Packet* packet);
	Packet* Receive(Packet* outPacket);
	Packet* Receive(b8 data);
	u16 Checkout(void);
	Address6 GetLastReceiveAddress(void);

	u32 send(Tool::Network::Datagram* data);
	int receive(WSABUF* buffer);
private:
	Datagram* data;
	SOCKET sock;
	sockaddr_in6 lastReceiveAddress;
	int length;
	WSA* wsa;
};

