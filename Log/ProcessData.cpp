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
        DWORD getProcessId()
        {
#ifdef WINDOWS
            return GetCurrentProcessId();
#elif defined(LINUX)
            return getpid();
#endif
        }
        ProcessData::ProcessData() :ID(getProcessId())
        {
        }
        UTF8* ProcessData::getData(const UTF8* pattern) const
        {
            UTF8* te = new UTF8[11];
            itca(ID, te, 10);
            return te;
        }
    }
}