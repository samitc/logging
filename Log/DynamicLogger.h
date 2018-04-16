#ifndef _DYNAMICLOG_H_
#define _DYNAMICLOG_H_
#include "Logger.h"
#if defined(WINDOWS)
#include <Windows.h>
#elif defined(LINUX)
#endif
#include <atomic>
#include <thread>
#include "XmlLogger.h"
#include "GlobalDefinitions.h"
namespace Sys
{
    namespace Logging
    {
        class DynamicLogger :public Logger
        {
        public:
            DynamicLogger() = delete;
            DynamicLogger(DynamicLogger&&) = delete;
            DynamicLogger(const char* fileName, ConcurrencyLevel level = ConcurrencyLevel::MEDIUM);
            DynamicLogger(const char* fileName, int concurrencyLevel);
            ~DynamicLogger();
        private:
            static void scanThread(DynamicLogger *logger);
            XmlLogger loadXml(const char*);
            std::thread scanTh;
            std::atomic_flag isExit;
#if defined(WINDOWS)
            HANDLE exitHandle;
#elif defined(LINUX)
#endif
            String name;
            XmlLogger xml;
        };
    }
}
#endif