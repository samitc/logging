#include "ProcessDataPattern.h"
#include "ProcessData.h"
namespace Sys
{
    namespace Logging
    {
        ProcessDataPattern::ProcessDataPattern() :cacheDataProcess(new ProcessData())
        {
        }
        ProcessDataPattern::~ProcessDataPattern()
        {
            delete cacheDataProcess;
        }
        IData * ProcessDataPattern::getPattern() const
        {
            return cacheDataProcess;
        }
        bool ProcessDataPattern::toDelete()
        {
            return false;
        }
    }
}