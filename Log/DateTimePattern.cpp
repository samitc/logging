#include "DateTimePattern.h"
#include "DateTime.h"
namespace Sys
{
    namespace Logging
    {
        IData * Sys::Logging::DateTimePattern::getPattern() const
        {
            return new DateTime();
        }
        bool DateTimePattern::toDelete()
        {
            return true;
        }
    }
}