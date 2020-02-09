#include "INCLUDE.H"
class Tool::Network::IP6
{
public:
	IP6(b32 iP);
	IP6(std::string* iP);
	IP6(std::wstring* iP);
	IP6(s8 iP);
	IP6(s16 iP);
	
	std::string* Tostring	(void)				const;
	std::wstring* Towstring	(void)				const;

	u32 Tostring			(std::string* iP)	const;
	u32 Towstring			(std::wstring* iP)	const;
	s8	Tos8				(void)				const;
	s16 Tos16				(void)				const;
	u32 Tos8				(s8 address)		const;
	u32 Tos16				(s16 address)		const;

	b32 Tob32				(void)				const ;
private:
	w32 address[4];
};
