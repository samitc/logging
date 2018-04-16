#include "Msg.h"
namespace Sys
{
    namespace Logging
    {
        UTF8 * Msg::getData(const UTF8 * pattern) const
        {
            const UTF8 str[] = "~!@";
            return createStr(str);
        }
        int Msg::getNumber() const
        {
            return 0;
        }
    }
}