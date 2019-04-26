#include "Msg.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
        UTF8* Msg::msgStr = "~!@";
        const UTF8 * Msg::getData(const UTF8 * pattern) const
        {
            return (UTF8*)Msg::msgStr;
        }
    }
}