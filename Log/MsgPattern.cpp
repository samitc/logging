#include "MsgPattern.h"
#include "Msg.h"
namespace Sys
{
    namespace Logging
    {
        MsgPattern::MsgPattern() :cacheMsg(new Msg())
        {
        }
        MsgPattern::~MsgPattern()
        {
            delete cacheMsg;
        }
        IData * Sys::Logging::MsgPattern::getPattern() const
        {
            return cacheMsg;
        }
        bool MsgPattern::toDelete()
        {
            return false;
        }
    }
}