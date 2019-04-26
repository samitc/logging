#include "LoggerName.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
        LoggerName::LoggerName(const String &loggerName) :loggerName(loggerName)
        {
        }
        const UTF8 * Sys::Logging::LoggerName::getData(const UTF8 * pattern) const
        {
            return loggerName.c_str();
        }
    }
}