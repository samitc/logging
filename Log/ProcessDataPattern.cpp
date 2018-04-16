#include "ProcessDataPattern.h"
#include "ProcessData.h"
namespace Sys
{
    namespace Logging
    {
        IData * ProcessDataPattern::getPattern() const
        {
            return new ProcessData();
        }
    }
}