#include "ProcessNamePattern.h"
#include "ProcessName.h"
namespace Sys
{
    namespace Logging
    {
        IData * ProcessNamePattern::getPattern() const
        {
            return new ProcessName();
        }
    }
}