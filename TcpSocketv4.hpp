#include "Network.hpp"
#include "IP.hpp"
#include <vector>
#include <type_traits>

namespace Tool { namespace Network{

	class TcpSocketv4
	{
	public:
		TcpSocketv4();
		int Listen(int backLog);
		TcpSocketv4 Accept(bool blocking);
		int Bind(IPv4 ip, uint16_t port);
		int Connect(IPv4 ip, uint16_t port);
		SOCKET Sock() const;


		template<class t>
		std::vector<t>* Recieve(std::vector<t>* data)
		{
			recv(sock, data->data(), data->capacity(), 0);
			return data;
		}

		template<class t>
		std::vector<t>* Recieve(std::vector<t>* data, size_t count)
		{
			data->resize(count);
			recv(sock, data->data(), count * sizeof(t), 0);
			return data;
		}

		template<class t>
		std::vector<t>* Recieve(size_t count)
		{
			std::vector<t> * data = new std::vector<t>();
			data->resize(count);
			recv(sock, data->data(), count * sizeof(t), 0);
			return data;
		}


		template<class t>
		int Send(std::vector<t> data)
		{
			return send(sock, data.data(), data.size(), 0);
		}



		~TcpSocketv4();
	private:
		TcpSocketv4(SOCKET socket);
		SOCKET sock;
		SOCKADDR remoteAddress;
	};
}
}