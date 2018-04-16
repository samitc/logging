#include "LogLevelPattern.h"
#include "LogLevel.h"
namespace Sys
{
    namespace Logging
    {
        IData * LogLevelPattern::getPattern() const
        {
            return new LogLevel();
        }
    }
}