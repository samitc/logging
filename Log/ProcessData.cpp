#include "ProcessData.h"
#include "CharUtilities.h"
#if defined(WINDOWS)
#include <Windows.h>
#elif defined(LINUX)
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
namespace Sys
{
    namespace Logging
    {
#ifdef WINDOWS
        ProcessData::ProcessData() :ID(GetCurrentProcessId())
#elif defined(LINUX)
        ProcessData::ProcessData() : ID(getpid())
#endif
        {
        }
        UTF8 * ProcessData::getData(const UTF8 * pattern) const
        {
            UTF8 *te = new UTF8[11];
            itca(ID, te, 10);
            return te;
        }
        int ProcessData::getNumber() const
        {
            return 2;
        }
    }
}