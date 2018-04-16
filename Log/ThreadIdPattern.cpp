#include "ThreadIdPattern.h"
#include "ThreadId.h"
namespace Sys
{
    namespace Logging
    {
        IData * ThreadIdPattern::getPattern() const
        {
            return new ThreadId();
        }
    }
}