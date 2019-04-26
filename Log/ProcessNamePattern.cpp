#include "ProcessNamePattern.h"
#include "ProcessName.h"
namespace Sys
{
    namespace Logging
    {
        ProcessNamePattern::ProcessNamePattern() :cacheProcessName(new ProcessName())
        {
        }
        ProcessNamePattern::~ProcessNamePattern()
        {
            delete cacheProcessName;
        }
        IData * ProcessNamePattern::getPattern() const
        {
            return cacheProcessName;
        }
        bool ProcessNamePattern::toDelete()
        {
            return false;
        }
    }
}