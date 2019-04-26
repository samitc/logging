#ifndef _IDATA_H_
#define _IDATA_H_
#include "GlobalDefinitions.h"
namespace Sys
{
	namespace Logging
	{
		class IData
		{
		public:
			virtual const UTF8 * getData(const UTF8 * pattern) const = 0;
			virtual ~IData() = default;
		};
	}
}
#endif