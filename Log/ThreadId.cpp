#include "ThreadId.h"
#include "CharUtilities.h"
#if defined(WINDOWS)
#include <Windows.h>
#elif defined(LINUX)
#include <unistd.h>
#include <sys/syscall.h>
#endif
namespace Sys
{
    namespace Logging
    {
        size_t getThreadId()
        {
#if defined(WINDOWS)
            return GetCurrentThreadId();
#elif defined(LINUX)
            return syscall(SYS_gettid);
#endif
        }
        ThreadId::ThreadId() :id(getThreadId())
        {
        }
        UTF8* ThreadId::getData(const UTF8* pattern) const
        {
            UTF8* te = new UTF8[11];
            itca(id, te, 10);
            return te;
        }
    }
}