#ifndef _LOGFILTER_H_
#define _LOGFILTER_H_
#include <functional>
#include <list>
#include "GlobalDefinitions.h"
#include "LString.h"
namespace Sys
{
	namespace Logging
	{
		class Logger;
		class LogFilter
		{
		public:
			LogFilter();
			~LogFilter() = default;
			void setFilterFunction(const std::function<bool(const String &)>&);
			void addFilterString(String &&str);
			bool filter(const String&) const;
		private:
			std::function<bool(const String &logStatement)> filterFunc;
			std::list<String> filterStr;
		};
	}
}
#endif