#include "Address6.h"
#include "WSA.h"
#include "IP6.h"

namespace Tool
{
	namespace Network
	{
		Address6::Address6(sockaddr_in6 & address)
		{
			this->address = address;
		}
		Address6::Address6(std::string * address)
		{
			this->address = getAddressFromString((const char*)(address->c_str()));
		}
		Address6::Address6(std::wstring * address)
		{
			this->address = getAddressFromString((const wchar_t*)(address->c_str()));
		}
		Address6::Address6(const char* address)
		{
			this->address = getAddressFromString((const char*)address);
		}
		Address6::Address6(const wchar_t* address)
		{
			this->address = getAddressFromString((const wchar_t*)address);
		}
		Address6::Address6(IP6 address)
		{
			this->address.sin6_flowinfo = 0;
			this->address.sin6_scope_id = 0;
			this->address.sin6_family = AF_INET6;
			*((uint32_t)this->address.sin6_addr.u.Word) = *((uint32_t)address.Tob32());
			*((uint32_t)this->address.sin6_addr.u.Word + 4) = *((uint32_t)address.Tob32() + 4);
			*((uint32_t)this->address.sin6_addr.u.Word + 8) = *((uint32_t)address.Tob32() + 8);
			*((uint32_t)this->address.sin6_addr.u.Word + 12) = *((uint32_t)address.Tob32() + 12);
		}
		Address6::Address6(std::string * iP, uint16_t port, uint32_t scope)
		{
			WSA was;
			this->address = getAddressFromString((const char*)(iP->c_str()));
			this->address.sin6_port = htons(port);
			this->address.sin6_scope_id = htonl(scope);
		}
		Address6::Address6(std::wstring * iP, uint16_t port, uint32_t scope)
		{
			WSA was;
			this->address = getAddressFromString((const wchar_t*)(iP->c_str()));
			this->address.sin6_port = htons(port);
			this->address.sin6_scope_id = htonl(scope);
		}
		Address6::Address6(const char* iP, uint16_t port, uint32_t scope)
		{
			WSA was;
			this->address = getAddressFromString((const char*)iP);
			this->address.sin6_port = htons(port);
			this->address.sin6_scope_id = htonl(scope);
		}
		Address6::Address6(const wchar_t* iP, uint16_t port, uint32_t scope)
		{
			WSA was;
			this->address = getAddressFromString((const wchar_t*)iP);
			this->address.sin6_port = htons(port);
			this->address.sin6_scope_id = htonl(scope);
		}
		Address6::Address6(IP6 address, uint16_t port, uint32_t scope)
		{
			WSA was;
			this->address.sin6_flowinfo = 0;
			this->address.sin6_family = AF_INET6;
			*((b32)this->address.sin6_addr.u.Word)		= *((b32)address.Tob32());
			*((b32)this->address.sin6_addr.u.Word + 4)	= *((b32)address.Tob32() + 4);
			*((b32)this->address.sin6_addr.u.Word + 8)	= *((b32)address.Tob32() + 8);
			*((b32)this->address.sin6_addr.u.Word + 12) = *((b32)address.Tob32() + 12);
			this->address.sin6_port = htons(port);
			this->address.sin6_scope_id = htonl(scope);
		}

		sockaddr_in6 Address6::getAddressFromString(const char* address)
		{
			WSA was;
			char buffer[INET6_ADDRSTRLEN];
			char buffer2[INET6_ADDRSTRLEN];
			const char* port;
			sockaddr_in6 addr;
			int addrlen = sizeof(addr);
			if(WSAStringToAddressA((LPSTR)address, AF_INET6, 0, (sockaddr*) &addr, &addrlen))
			{
				int addrlen = sizeof(addr);
				strcpy((char*)buffer2, (char*)address);
				strtok((char*)buffer2,":");
				if (!(port = (const char*)strtok(NULL, ":")))
					port = (const char*) "";
				sprintf((char*)buffer,"[::ffff:%s]:%s", buffer2, port);
				if(WSAStringToAddressA((LPSTR)buffer, AF_INET6, 0, (sockaddr*) &addr, &addrlen))
				{
					printf("%s\n",buffer);
					printf("WSAStringToAddressA Error:%i", WSAGetLastError());
				}
				else
					printf("%s\n",buffer);
			}
			return addr;
		}
		sockaddr_in6 Address6::getAddressFromString(const wchar_t* address)
		{
			WSA was;
			wchar_t buffer[INET6_ADDRSTRLEN];
			wchar_t buffer2[INET6_ADDRSTRLEN];
			wchar_t* port;
			sockaddr_in6 addr;
			int addrlen = sizeof(addr);
			if(WSAStringToAddressW((LPWSTR)address, AF_INET6, 0, (sockaddr*) &addr, &addrlen))
			{
				int addrlen = sizeof(addr);
				wcscpy((wchar_t*)buffer2, (wchar_t*)address);
				wcstok((wchar_t*)buffer2,L":");
				if (!(port = (const wchar_t*)wcstok(NULL, L":")))
					port = (const wchar_t*)L"";
				swprintf((wchar_t*)buffer,L"[::ffff:%s]:%s", buffer2, port);
				if(WSAStringToAddressW((LPWSTR)buffer, AF_INET6, 0, (sockaddr*) &addr, &addrlen))
				{
					wprintf(L"%s\n",buffer);
					wprintf(L"WSAStringToAddressA Error:%i", WSAGetLastError());
				}
				else
					wprintf(L"%s\n",buffer);
			}
			return addr;
		}

		sockaddr_in6 Address6::Tosockaddr(void) const
		{
			return this->address;
		}
		std::string * Address6::Tostring(void) const
		{
			WSA was;
			std::string* out = new std::string();
			uint32_t outlen = INET6_ADDRSTRLEN;
			out->resize(INET6_ADDRSTRLEN);
			printf("%i:%i",this->address.sin6_addr,this->address.sin6_port);
			WSAAddressToStringA((sockaddr*) &(this->address), sizeof(sockaddr_in6), 0, (LPSTR)out->c_str(), &outlen);
			printf("%i:%i",this->address.sin6_addr,this->address.sin6_port);
			out->resize(outlen);
			return out;
		}
		std::wstring * Address6::Towstring(void) const
		{
			WSA was;
			std::wstring* out = new std::wstring();
			uint32_t outlen = INET6_ADDRSTRLEN;
			out->resize(INET6_ADDRSTRLEN);
			WSAAddressToStringW((sockaddr*) &(this->address), sizeof(sockaddr_in6), 0, (LPWSTR)out->c_str(), &outlen);
			out->resize(outlen);
			return out;
		}
		char* Address6::Tochar(void) const
		{
			char* out = new char[INET6_ADDRSTRLEN];
			GetconstcharAddress(out);
			return out;
		}
		wchar_t* Address6::Towchar_t(void) const
		{
			wchar_t* out = new wchar_t[INET6_ADDRSTRLEN];
			Getwchar_tAddress(out);
			return out;
		}

		uint32_t Address6::GetstringAddress(std::string* address) const
		{
			WSA was;
			uint32_t outlen = INET6_ADDRSTRLEN;
			address->resize(INET6_ADDRSTRLEN);
			WSAAddressToStringA((sockaddr*) &(this->address), sizeof(sockaddr_in6), 0, (LPSTR)address->c_str(), &outlen);
			address->resize(outlen);
			return outlen;
			return 0;
		}
		uint32_t Address6::GetwstringAddress(std::wstring* address) const
		{
			WSA was;
			uint32_t outlen = INET6_ADDRSTRLEN;
			address->resize(INET6_ADDRSTRLEN);
			WSAAddressToStringW((sockaddr*) &(this->address), sizeof(sockaddr_in6), 0, (LPWSTR)address->c_str(), &outlen);
			address->resize(outlen);
			return outlen;
			return 0;
		}

		uint32_t Address6::GetcharAddress(const char* address) const
		{
			WSA was;
			uint32_t outlen = INET6_ADDRSTRLEN;
			WSAAddressToStringA((sockaddr*) &(this->address), sizeof(sockaddr_in6), 0, (LPSTR)address, &outlen); 
			return outlen;
		}
		uint32_t Address6::Getwchar_tAddress(const wchar_t* address) const
		{
			WSA was;
			uint32_t outlen = INET6_ADDRSTRLEN;
			WSAAddressToStringW((sockaddr*) &(this->address), sizeof(sockaddr_in6), 0, (LPWSTR)address, &outlen); 
			return outlen;
		}
		uint16_t Address6::GetPort(void) const
		{
			WSA was;
			return ntohs(address.sin6_port);
		}
		uint32_t Address6::GetScope(void) const
		{
			WSA was;
			return ntohl(address.sin6_scope_id);
		}

		IP6 Address6::GetIP(void) const
		{
			return IP6((b32)this->address.sin6_addr.u.Word);
		}
		std::string * Address6::GetstringIP(void) const
		{
			char out[INET6_ADDRSTRLEN];
			GetcharIP(out); 
			return new std::string((const char*)out);
		}
		std::wstring * Address6::GetwstringIP(void) const
		{
			wchar_t out[INET6_ADDRSTRLEN];
			Getwchar_tIP(out); 
			return new std::wstring((const wchar_t*)out);
		}
		char* Address6::GetcharIP(void) const
		{
			char* out = new char[INET6_ADDRSTRLEN];
			GetcharIP(out); 
			return out;
		}
		wchar_t* Address6::Getwchar_tIP(void) const
		{
			wchar_t* out = new wchar_t[INET6_ADDRSTRLEN];
			Getwchar_tIP(out);
			return out;
		}

		uint32_t Address6::GetstringIP(std::string * iP) const
		{
			char out[INET6_ADDRSTRLEN];
			uint32_t outlen;
			outlen = GetcharIP(out);
			iP->append((const char*)out);
			return outlen;
		}
		uint32_t Address6::GetwstringIP(std::wstring * iP) const
		{
			wchar_t out[INET6_ADDRSTRLEN];
			uint32_t outlen;
			outlen = Getwchar_tIP(out);
			iP->append((const wchar_t*)out);
			return outlen;
		}
		uint32_t Address6::GetcharIP(const char* iP) const
		{
			WSA was;
			uint32_t outlen = INET6_ADDRSTRLEN;
			sockaddr_in6 addr;
			addr.sin6_addr = this->address.sin6_addr;
			addr.sin6_family = AF_INET6;
			addr.sin6_flowinfo = 0;
			addr.sin6_port = 0;
			addr.sin6_scope_id = 0;
			WSAAddressToStringA((sockaddr*)&addr, sizeof(sockaddr_in6), 0, (LPSTR)iP, &outlen);
			return outlen;
		}
		uint32_t Address6::Getwchar_tIP(const wchar_t* iP) const
		{
			WSA was;
			uint32_t outlen = INET6_ADDRSTRLEN;
			sockaddr_in6 addr;
			addr.sin6_addr = this->address.sin6_addr;
			addr.sin6_family = AF_INET6;
			addr.sin6_flowinfo = 0;
			addr.sin6_port = 0;
			addr.sin6_scope_id = 0;
			WSAAddressToStringW((sockaddr*)&addr, sizeof(sockaddr_in6), 0, (LPWSTR)iP, &outlen);
			return outlen;
		}

	}
}
