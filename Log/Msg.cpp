#include "Msg.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
        UTF8* Msg::msgStr = "~!@";
        UTF8 * Msg::getData(const UTF8 * pattern) const
        {
            return (UTF8*)Msg::msgStr;
        }
    }
}