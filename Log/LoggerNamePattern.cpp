#include "LoggerNamePattern.h"
#include "LoggerName.h"
namespace Sys
{
    namespace Logging
    {
        LoggerNamePattern::LoggerNamePattern(String&& loggerName) :loggerName(std::move(loggerName)), cacheLoggerName(new LoggerName(loggerName))
        {
        }
        LoggerNamePattern::~LoggerNamePattern()
        {
            delete cacheLoggerName;
        }
        IData * Sys::Logging::LoggerNamePattern::getPattern() const
        {
            return cacheLoggerName;
        }
        bool LoggerNamePattern::toDelete()
        {
            return false;
        }
    }
}