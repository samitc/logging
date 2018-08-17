#include "LogFilter.h"
#include <algorithm>
#include "LString.h"
namespace Sys
{
    namespace Logging
    {
        LogFilter::LogFilter() :filterFunc([](const String&) {return true; }), filterStr()
        {
        }
        void LogFilter::setFilterFunction(const std::function<bool(const String&)>&filterFunc)
        {
            this->filterFunc = filterFunc;
        }
        void LogFilter::addFilterString(String &&str)
        {
            filterStr.push_back(std::move(str));
        }
        bool LogFilter::filter(const String &str) const
        {
            if (!filterFunc(str))
            {
                return false;
            }
            return std::all_of(filterStr.cbegin(), filterStr.cend(), [&str](const String& filt)
            {
                return find(str.c_str(), filt.c_str());
            });
        }
    }
}