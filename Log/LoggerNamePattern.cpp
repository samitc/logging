#include "LoggerNamePattern.h"
#include "LoggerName.h"
namespace Sys
{
    namespace Logging
    {
        LoggerNamePattern::LoggerNamePattern(String && loggerName) :loggerName(std::move(loggerName))
        {
        }
        IData * Sys::Logging::LoggerNamePattern::getPattern() const
        {
            return new LoggerName(loggerName);
        }
    }
}