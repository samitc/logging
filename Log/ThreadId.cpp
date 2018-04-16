#include "ThreadId.h"
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
#if defined(WINDOWS)
        ThreadId::ThreadId() :id(GetCurrentThreadId())
#elif defined(LINUX)
        ThreadId::ThreadId() : id(syscall(SYS_gettid))
#endif
        {
        }
        UTF8 * ThreadId::getData(const UTF8 * pattern) const
        {
            UTF8 *te = new UTF8[11];
            itca(id, te, 10);
            return te;
        }
        int ThreadId::getNumber() const
        {
            return 6;
        }
    }
}