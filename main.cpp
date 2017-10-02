#include "Network.hpp"
#include "IPv4.hpp"
#include "SocketIPv4.hpp"
#include <iostream>
DCB dcb;
using namespace Tool::Network;
using namespace std;


void test()
{
	char c;
	SocketIPv4 sock(ipv4, Socket::stream, Socket::tcp);
	std::cout << "Choose mode" << endl;
	c = std::cin.get();
	switch (c)
	{
	case 's':
		cout << "Server" << endl;
		if (sock.GetSocket() == INVALID_SOCKET)
			cout << "Invalid Socket!" << endl;
			sock.Bind(IPv4::any(), 40942);
			sock.Listen();

		try
		{
			sock.Accept(true);
			cout << "Connected" << endl;
		}
		catch (...)
		{
			switch (WSAGetLastError())
			{
			case WSANOTINITIALISED:
				cout << "WSA Not initialised!" << endl;
				break;
			case WSAECONNRESET:
				cout << "WSA Connection Reset!" << endl;
				break;
			case WSAEFAULT:
				cout << "WSA Fault!" << endl;
				break;
			case WSAEINTR:
				cout << "WSA Blocked!" << endl;
				break;
			case WSAEINVAL:
				cout << "WSA no listen!" << endl;
				break;
			case WSAEINPROGRESS:
				cout << "WSA in progress!" << endl;
				break;
			case WSAEMFILE:
				cout << "WSA M File!" << endl;
				break;
			case WSAENETDOWN:
				cout << "WSA Network Subsystem!" << endl;
				break;
			case WSAENOBUFS:
				cout << "WSA No Buffer!" << endl;
				break;
			case WSAENOTSOCK:
				cout << "WSA Not a socket!" << endl;
				break;
			case WSAEOPNOTSUPP:
				cout << "WSA Not supportet!" << endl;
				break;
			case WSAEWOULDBLOCK:
				cout << "WSA Non Blocking!" << endl;
				break;
			default:
				cout << "Another Error!" << endl;
			}
		}
		break;
	case 'c':
		cout << "Client" << endl;
		if (sock.Connect(IPv4("127.0.0.1"), 40942))
			cout << "Fail to connect!" << endl;
		cout << WSAGetLastError() << endl;

	}
}

int main(int argc, char* argv[])
{
	uint8_t ip3[] = { 127, 0, 0, 1 };
	IPv4 ip("127.0.0.1");
	IPv4 ip2(ip3);
	IPv4 ip4 = IPv4::any();
	cout << hex << ip.data() << endl;
	cout << hex << ip2.data() << endl;
	cin.get();
	return 0;
}

