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
        const UTF8* ThreadId::getData(const UTF8* pattern) const
        {
            itca(id, ts, TS_SIZE - 1);
            return ts;
        }
    }
}