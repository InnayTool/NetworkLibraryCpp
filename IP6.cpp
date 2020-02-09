#include "IP6.h"
#include "WSA.h"
namespace Tool
{
	namespace Network
	{
		IP6::IP6(b32 iP)
		{
			this->address[0] = iP[0];
			this->address[1] = iP[1];
			this->address[2] = iP[2];
			this->address[3] = iP[3];

		}
		IP6::IP6(std::wstring* iP)
		{
			SOCKADDR_IN6 sockaddress;
			int length = sizeof(SOCKADDR_IN6);
			WSA wsa;
			WSAStringToAddressW((LPWSTR)iP->c_str(), AF_INET6, NULL, (SOCKADDR*) &sockaddress, &length); 

			this->address[0] = ((b32)sockaddress.sin6_addr.u.Word)[0];
			this->address[1] = ((b32)sockaddress.sin6_addr.u.Word)[1];
			this->address[2] = ((b32)sockaddress.sin6_addr.u.Word)[2];
			this->address[3] = ((b32)sockaddress.sin6_addr.u.Word)[3];
		}
		IP6::IP6(std::string* iP)
		{
			SOCKADDR_IN6 sockaddress;
			int length = sizeof(SOCKADDR_IN6);
			WSA wsa;
			WSAStringToAddressA((LPSTR)iP->c_str(), AF_INET6, NULL, (SOCKADDR*) &sockaddress, &length); 
			this->address[0] = ((b32)sockaddress.sin6_addr.u.Word)[0];
			this->address[1] = ((b32)sockaddress.sin6_addr.u.Word)[1];
			this->address[2] = ((b32)sockaddress.sin6_addr.u.Word)[2];
			this->address[3] = ((b32)sockaddress.sin6_addr.u.Word)[3];
		}
		IP6::IP6(s8 iP)
		{
			SOCKADDR_IN6 sockaddress;
			int length = sizeof(SOCKADDR_IN6);
			WSA wsa;
			WSAStringToAddressA((LPSTR)iP, AF_INET6, NULL, (SOCKADDR*) &sockaddress, &length); 
			this->address[0] = ((b32)sockaddress.sin6_addr.u.Word)[0];
			this->address[1] = ((b32)sockaddress.sin6_addr.u.Word)[1];
			this->address[2] = ((b32)sockaddress.sin6_addr.u.Word)[2];
			this->address[3] = ((b32)sockaddress.sin6_addr.u.Word)[3];
		}
		IP6::IP6(s16 iP)
		{
			SOCKADDR_IN6 sockaddress;
			int length = sizeof(SOCKADDR_IN6);
			WSA wsa;
			WSAStringToAddressW((LPWSTR)iP, AF_INET6, NULL, (SOCKADDR*) &sockaddress, &length); 
			this->address[0] = ((b32)sockaddress.sin6_addr.u.Word)[0];
			this->address[1] = ((b32)sockaddress.sin6_addr.u.Word)[1];
			this->address[2] = ((b32)sockaddress.sin6_addr.u.Word)[2];
			this->address[3] = ((b32)sockaddress.sin6_addr.u.Word)[3];
		}
		b32 IP6::Tob32(void) const
		{
			b32 out = new w32[4];
			out[0] = this->address[0];
			out[1] = this->address[1];
			out[2] = this->address[2];
			out[3] = this->address[3];
			return out;
		}
		std::string* IP6::Tostring(void) const
		{
			std::string* out = new std::string();
			Tostring(out);
			return out;
		}
		std::wstring* IP6::Towstring(void) const
		{
			std::wstring* out = new std::wstring();
			Towstring(out);
			return out;
		}
		u32 IP6::Tostring(std::string* iP) const
		{
			iP->resize(INET6_ADDRSTRLEN);
			return Tos8((s8) iP->c_str());
		}
		u32 IP6::Towstring(std::wstring* iP) const
		{
			iP->resize(INET6_ADDRSTRLEN);
			return Tos16((s16) iP->c_str());
		}
		s8 IP6::Tos8(void) const
		{
			s8 out = new c8[INET6_ADDRSTRLEN];
			Tos8(out);
			return out;
		}
		s16 IP6::Tos16(void) const
		{
			s16 out = new c16[INET6_ADDRSTRLEN];
			Tos16(out);
			return out;
		}
		u32 IP6::Tos8(s8 address) const
		{
			u32 outlen = sizeof(sockaddr_in6);
			sockaddr_in6 addr;
			((b32)addr.sin6_addr.u.Word)[0] = this->address[0];
			((b32)addr.sin6_addr.u.Word)[1] = this->address[1];
			((b32)addr.sin6_addr.u.Word)[2] = this->address[2];
			((b32)addr.sin6_addr.u.Word)[3] = this->address[3];
			addr.sin6_family = AF_INET6;
			addr.sin6_flowinfo = 0;
			addr.sin6_scope_id = 0;
			addr.sin6_port = 0;
			WSAAddressToStringA((SOCKADDR*)&addr, sizeof(addr), 0, (LPSTR)address, (LPDWORD)&outlen);
			return outlen;
		}
		u32 IP6::Tos16(s16 address) const
		{
			u32 outlen = sizeof(sockaddr_in6);
			sockaddr_in6 addr;
			((b32)addr.sin6_addr.u.Word)[0] = this->address[0];
			((b32)addr.sin6_addr.u.Word)[1] = this->address[1];
			((b32)addr.sin6_addr.u.Word)[2] = this->address[2];
			((b32)addr.sin6_addr.u.Word)[3] = this->address[3];
			addr.sin6_family = AF_INET6;
			addr.sin6_flowinfo = 0;
			addr.sin6_scope_id = 0;
			addr.sin6_port = 0;
			WSAAddressToStringW((SOCKADDR*)&addr, sizeof(addr), 0, (LPWSTR)address, (LPDWORD)&outlen);
			return outlen;
		}
	}
}
