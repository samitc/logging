#include "MsgPattern.h"
#include "Msg.h"
namespace Sys
{
    namespace Logging
    {
        IData * Sys::Logging::MsgPattern::getPattern() const
        {
            return new Msg();
        }
    }
}