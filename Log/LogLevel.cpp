#include "LogLevel.h"
namespace Sys
{
    namespace Logging
    {
        UTF8 * LogLevel::getData(const UTF8 * pattern) const
        {
            const UTF8 str[] = "@`~";
            return createStr(str);
        }
        int LogLevel::getNumber() const
        {
            return 4;
        }
    }
}