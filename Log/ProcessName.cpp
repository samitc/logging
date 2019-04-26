#include "ProcessName.h"
#include "CharUtilities.h"
#if defined(WINDOWS)
#include <Windows.h>
#include <Psapi.h>
#elif defined(LINUX)
#include <fstream>
#endif
namespace Sys
{
    namespace Logging
    {
        void getProcessName(char* name,int BUFFER_SIZE)
        {
#if defined(WINDOWS)
            DWORD ID = GetCurrentProcessId();
            HANDLE Handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ID);
            if (Handle)
            {
                GetProcessImageFileNameA(Handle, name, BUFFER_SIZE);
            }
#elif defined(LINUX)
            std::ifstream fileName("/proc/self/status");
            const int SIZE_OF_BUFFER = 1024 + 1;
            char programName[SIZE_OF_BUFFER];
            fileName.getline(programName, SIZE_OF_BUFFER);
            char* p = programName;
            while (*p != ' ')
            {
                ++p;
            }
            while (*p == ' ')
            {
                ++p;
            }
            strcpy(name, p);
#endif
        }
        Sys::Logging::ProcessName::ProcessName()
        {
            getProcessName(name, BUFFER_SIZE);
        }
        UTF8 * ProcessName::getData(const UTF8 * pattern) const
        {
            const UTF8* end = name;
            while (*end != 0)
            {
                ++end;
            }
            const UTF8* start = end;
            while (*start != '\\')
            {
                --start;
            }
            ++start;
            return createStr(start);
        }
    }
}