#include "Address4.h"
#include "IP4.h"
#include "WSA.h"

namespace Tool
{
	namespace Network
	{
		Address4::Address4(sockaddr_in & address)
		{
			this->address = address;
		}
		Address4::Address4(std::string & address)
		{
			this->address = getAddressFromString((const char*)(address.c_str()));
		}
		Address4::Address4(std::wstring & address)
		{
			this->address = getAddressFromString((const wchar_t*)(address.c_str()));
		}
		Address4::Address4(const char* address)
		{
			this->address = getAddressFromString((const char*)address);
		}
		Address4::Address4(const wchar_t* address)
		{
			this->address = getAddressFromString((const wchar_t*)address);
		}
		Address4::Address4(IP4 address)
		{

			this->address.sin_family = AF_INET;
			this->address.sin_addr.S_un.S_addr = address.Tow32();
		}
		Address4::Address4(std::string & iP, uint16_t port)
		{
			WSA was;
			this->address = getAddressFromString((const char*)(iP.c_str()));
			this->address.sin_port = htons(port);
		}
		Address4::Address4(std::wstring & iP, uint16_t port)
		{
			WSA was;
			this->address = getAddressFromString((const wchar_t*)(iP.c_str()));
			this->address.sin_port = htons(port);
		}
		Address4::Address4(const char* iP, uint16_t port)
		{
			WSA was;
			this->address = getAddressFromString((const char*)iP);
			this->address.sin_port = htons(port);
		}
		Address4::Address4(const char* iP, uint16_t port)
		{
			WSA was;
			this->address = getAddressFromString((const char*)iP);
			this->address.sin_port = htons(port);
		}
		Address4::Address4(IP4 address, uint16_t port)
		{
			WSA was;
			this->address.sin_family = AF_INET;
			this->address.sin_addr.S_un.S_addr = address.Tow32();
		}

		sockaddr_in Address4::getAddressFromString(const char* address)
		{
			WSA was;
			sockaddr_in addr;
			int addrlen = sizeof(addr);
			if(WSAStringToAddressA((LPSTR)address, AF_INET, 0,(sockaddr*) &addr, &addrlen)!= 0)
				throw WSAGetLastError();
			return addr;
		}
		sockaddr_in Address4::getAddressFromString(const wchar_t* address)
		{
			WSA was;
			sockaddr_in addr;
			int addrlen = sizeof(addr);
			if(WSAStringToAddressW((LPWSTR)address, AF_INET, 0,(sockaddr*) &addr, &addrlen)!= 0)
				throw WSAGetLastError();
			return addr;
		}

		sockaddr_in Address4::Tosockaddr(void) const
		{
			return this->address;
		}
		std::string * Address4::Tostring(void) const
		{
			WSA was;
			std::string* out = new std::string();
			uint32_t outlen = INET_ADDRSTRLEN;
			out->resize(INET_ADDRSTRLEN);
			WSAAddressToStringA((sockaddr*) &(this->address), sizeof(sockaddr_in), 0, (LPSTR)out->c_str(), &outlen);
			out->resize(outlen);
			return out;
		}
		std::wstring * Address4::Towstring(void) const
		{
			WSA was;
			std::wstring* out = new std::wstring();
			uint32_t outlen = INET_ADDRSTRLEN;
			out->resize(INET_ADDRSTRLEN);
			WSAAddressToStringW((sockaddr*) &(this->address), sizeof(sockaddr_in), 0, (LPWSTR)out->c_str(), &outlen);
			out->resize(outlen);
			return out;
		}
		char* Address4::Tochar(void) const
		{
			char* out = new c8[INET_ADDRSTRLEN];
			GetcharAddress(out);
			return out;
		}
		wchar_t* Address4::Towchar_t(void) const
		{
			wchar_t* out = new c16[INET_ADDRSTRLEN];
			Getwchar_tAddress(out);
			return out;
		}

		uint32_t Address4::GetstringAddress(std::string* address) const
		{
			WSA was;
			uint32_t outlen = INET_ADDRSTRLEN;
			address->resize(INET_ADDRSTRLEN);
			WSAAddressToStringA((sockaddr*) &(this->address), sizeof(sockaddr_in), 0, (LPSTR)address->c_str(), &outlen);
			address->resize(outlen);
			return outlen;
			return 0;
		}
		uint32_t Address4::GetwstringAddress(std::wstring* address) const
		{
			WSA was;
			uint32_t outlen = INET_ADDRSTRLEN;
			address->resize(INET_ADDRSTRLEN);
			WSAAddressToStringW((sockaddr*) &(this->address), sizeof(sockaddr_in), 0, (LPWSTR)address->c_str(), &outlen);
			address->resize(outlen);
			return outlen;
			return 0;
		}

		uint32_t Address4::GetcharAddress(char* address) const
		{
			WSA was;
			uint32_t outlen;
			WSAAddressToStringA((sockaddr*) &(this->address), sizeof(sockaddr_in6), 0, (LPSTR)address, &outlen); 
			return outlen;
		}
		uint32_t Address4::Getwchar_tAddress(const wchar_t* address) const
		{
			WSA was;
			uint32_t outlen;
			WSAAddressToStringW((sockaddr*) &(this->address), sizeof(sockaddr_in), 0, (LPWSTR)address, &outlen); 
			return outlen;
		}
		uint16_t Address4::GetPort(void) const
		{
			WSA was;
			return ntohs(address.sin_port);
		}


		IP4 Address4::GetIP(void) const
		{
			return IP4((w32)this->address.sin_addr.S_un.S_addr);
		}
		std::string * Address4::GetstringIP(void) const
		{
			char out[INET_ADDRSTRLEN];
			GetcharIP(out);
			return new std::string((const char*)out);
		}
		std::wstring * Address4::GetwstringIP(void) const
		{
			wchar_t out[INET_ADDRSTRLEN];
			Getwchar_tIP(out);
			return new std::wstring((const wchar_t*)out);
		}
		char* Address4::GetcharIP(void) const
		{
			char out* = new c8[INET_ADDRSTRLEN];
			GetcharIP(out);
			return out;
		}
		wchar_t* Address4::Getwchar_tIP(void) const
		{
			wchar_t* out = new wchar_t[INET_ADDRSTRLEN];
			Getwchar_tIP(out);
			return out;
		}

		uint32_t Address4::GetstringIP(std::string & iP) const
		{
			char out[INET_ADDRSTRLEN];
			uint32_t outlen;
			outlen = GetcharIP(out);
			iP.append((const char*)out);
			return outlen;
		}
		uint32_t Address4::GetwstringIP(std::wstring & iP) const
		{
			c16 out[INET_ADDRSTRLEN];
			uint32_t outlen;
			outlen = Getwchar_tIP(out);
			iP.append((const wchar_t*)out);
			return outlen;
		}
		uint32_t Address4::GetcharIP(const char* iP) const
		{
			WSA was;
			uint32_t outlen = INET_ADDRSTRLEN;
			sockaddr_in addr;
			addr.sin_addr = this->address.sin_addr;
			addr.sin_family = AF_INET;
			addr.sin_port = 0;
			WSAAddressToStringA((sockaddr*)&addr, sizeof(sockaddr_in), 0, (LPSTR)iP, &outlen);
			return outlen;
		}
		uint32_t Address4::Getwchar_tIP(const wchar_t* iP) const
		{
			WSA was;
			uint32_t outlen = INET_ADDRSTRLEN;
			sockaddr_in addr;
			addr.sin_addr = this->address.sin_addr;
			addr.sin_family = AF_INET;
			addr.sin_port = 0;
			WSAAddressToStringW((sockaddr*)&addr, sizeof(sockaddr_in), 0, (LPWSTR)iP, &outlen);
			return outlen;
		}

	}
}