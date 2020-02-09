#include "IP4.h"
#include "WSA.h"
namespace Tool
{
	namespace Network
	{
		IP4::IP4(std::wstring* iP)
		{
			SOCKADDR_IN sockaddress;
			int length = sizeof(SOCKADDR_IN);
			WSA wsa;
			WSAStringToAddressW((LPWSTR)iP->c_str(), AF_INET, NULL, (SOCKADDR*) &sockaddress, &length); 
			this->address = sockaddress.sin_addr.S_un.S_addr;
		}
		IP4::IP4(std::string* iP)
		{
			SOCKADDR_IN sockaddress;
			int length = sizeof(SOCKADDR_IN);
			WSA wsa;
			WSAStringToAddressA((LPSTR)iP->c_str(), AF_INET, NULL, (SOCKADDR*) &sockaddress, &length); 
			this->address = sockaddress.sin_addr.S_un.S_addr;
		}
		IP4::IP4(s8 iP)
		{
			SOCKADDR_IN sockaddress;
			int length = sizeof(SOCKADDR_IN);
			WSA wsa;
			WSAStringToAddressA((LPSTR)iP, AF_INET, NULL, (SOCKADDR*) &sockaddress, &length); 
			this->address = sockaddress.sin_addr.S_un.S_addr;
		}
		IP4::IP4(s16 iP)
		{
			SOCKADDR_IN sockaddress;
			int length = sizeof(SOCKADDR_IN);
			WSA wsa;
			WSAStringToAddressW((LPWSTR)iP, AF_INET, NULL, (SOCKADDR*) &sockaddress, &length); 
			this->address = sockaddress.sin_addr.S_un.S_addr;
		}
		IP4::IP4(w32 iP)
		{
			this->address = iP;
		}
		u32 IP4::Tow32(void) const
		{
			return this->address;
		}
		std::string* IP4::Tostring(void) const
		{
			std::string* out = new std::string();
			Tostring(out);
			return out;
		}
		std::wstring* IP4::Towstring(void) const
		{
			std::wstring* out = new std::wstring();
			Towstring(out);
			return out;
		}
		u32 IP4::Tostring(std::string* iP) const
		{
			iP->resize(INET_ADDRSTRLEN);
			return Tos8((s8) iP->c_str());
		}
		u32 IP4::Towstring(std::wstring* iP) const
		{
			iP->resize(INET_ADDRSTRLEN);
			return Tos16((s16) iP->c_str());
		}
		s8 IP4::Tos8(void) const
		{
			s8 out = new c8[INET_ADDRSTRLEN];
			Tos8(out);
			return out;
		}
		s16 IP4::Tos16(void) const
		{
			s16 out = new c16[INET_ADDRSTRLEN];
			Tos16(out);
			return out;
		}
		u32 IP4::Tos8(s8 address) const
		{
			u32 outlen;
			sockaddr_in addr;
			addr.sin_addr.S_un.S_addr = this->address;
			addr.sin_family = AF_INET;
			addr.sin_port = 0;
			WSAAddressToStringA((SOCKADDR*)&addr, sizeof(addr), 0, (LPSTR)address, (LPDWORD)&outlen);
			return outlen;
		}
		u32 IP4::Tos16(s16 address) const
		{
			u32 outlen = INET_ADDRSTRLEN;
			sockaddr_in addr;
			addr.sin_addr.S_un.S_addr = this->address;
			addr.sin_family = AF_INET;
			addr.sin_port = 0;
			WSAAddressToStringW((SOCKADDR*)&addr, sizeof(addr), 0, (LPWSTR)address, (LPDWORD)&outlen);
			return outlen;
		}
	}
}
