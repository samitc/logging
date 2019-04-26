#include "LogLevelPattern.h"
#include "LogLevel.h"
namespace Sys
{
    namespace Logging
    {
        LogLevelPattern::LogLevelPattern() :cacheLogLevel(new LogLevel())
        {
        }
        LogLevelPattern::~LogLevelPattern()
        {
            delete cacheLogLevel;
        }
        IData * LogLevelPattern::getPattern() const
        {
            return cacheLogLevel;
        }
        bool LogLevelPattern::toDelete()
        {
            return false;
        }
    }
}