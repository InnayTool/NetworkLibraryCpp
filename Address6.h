#include "INCLUDE.H"

class Tool::Network::Address6
{
public:
	Address6(sockaddr_in6 &	address);
	Address6(std::string  *	address);
	Address6(std::wstring *	address);
	Address6(s8				address);
	Address6(s16			address);
	Address6(IP6			address);
		   
	Address6(std::string  *	iP, u16	port, u32 scope);
	Address6(std::wstring *	iP, u16	port, u32 scope);
	Address6(s8				iP, u16	port, u32 scope);
	Address6(s16			iP, u16	port, u32 scope);
	Address6(IP6			iP, u16	port, u32 scope);

	sockaddr_in6	Tosockaddr			(void) const;
	std::string	 *	Tostring			(void) const;
	std::wstring *	Towstring			(void) const;
	s8				Tos8				(void) const;
	s16				Tos16				(void) const;

	std::string	 *	GetstringIP			(void) const;
	std::wstring *	GetwstringIP		(void) const;
	s8				Gets8IP				(void) const;
	s16				Gets16IP			(void) const;
	IP6				GetIP				(void) const;

	u16				GetPort				(void) const;
	u32				GetScope			(void) const;

	u32				GetstringAddress	(std::string* address)	const;
	u32				GetwstringAddress	(std::wstring* address) const;
	u32				Gets8Address		(s8 address)			const;
	u32				Gets16Address		(s16 address)			const;

	u32				GetstringIP			(std::string* iP)		const;
	u32				GetwstringIP		(std::wstring* iP)		const;
	u32				Gets8IP				(s8 iP)					const;
	u32				Gets16IP			(s16 iP)				const;

private:
	inline sockaddr_in6 getAddressFromString(s8 address);
	inline sockaddr_in6 getAddressFromString(s16 address);

	sockaddr_in6 address;
};
