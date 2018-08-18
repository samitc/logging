#ifndef _GLOBALDEFINITIONS_H_
#define _GLOBALDEFINITIONS_H_
#ifdef DEFCONSTEXPER
	#define CONSTEXPR	constexpr
#else
	#define CONSTEXPR
#endif
#define CONSTEXPRN		constexpr
namespace Sys
{
	namespace Logging
	{
        using byte = unsigned char;
        using UTF8 = char;
	}
}
#endif