#include <chrono>
#include "../Log/Logger.h"
#include "../Log/XmlLogger.h"
#include <iostream>
#include "gtest/gtest.h"
#if defined(WINDOWS)
#include <Windows.h>
#elif defined(LINUX)
#include <unistd.h>
#include <sys/syscall.h>
#endif
#if defined(WINDOWS)
#define POPEN   _popen
#define PCLOSE  _pclose
#elif defined(LINUX)
#define POPEN   popen
#define PCLOSE  pclose
#endif
using namespace Sys::Logging;
namespace LogTesting {
    unsigned long getPid()
    {
#ifdef WINDOWS
        return GetCurrentProcessId();
#elif defined(LINUX)
        return getpid();
#endif
    }
    unsigned long getTid()
    {
#if defined(WINDOWS)
        return GetCurrentThreadId();
#elif defined(LINUX)
        return syscall(SYS_gettid);
#endif
    }
    int exec(const char* cmd, std::string &output)
    {
        char buffer[128];
        FILE *pipe = POPEN(cmd, "r");
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != nullptr)
                output += buffer;
        }
        return PCLOSE(pipe);
    }
#define TEST_METHOD_NAME loggerFileMaxConcurrencyTest
#define LOG_CONCURRENCY_LEVEL ConcurrencyLevel::ALL
#include "GeneralTest.h"
#undef TEST_METHOD_NAME
#undef LOG_CONCURRENCY_LEVEL
#define TEST_METHOD_NAME loggerFileMinConcurrencyTest
#define LOG_CONCURRENCY_LEVEL ConcurrencyLevel::ONE
#include "GeneralTest.h"
#undef TEST_METHOD_NAME
#undef LOG_CONCURRENCY_LEVEL
#define TEST_METHOD_NAME loggerFileNoneConcurrencyTest
#define LOG_CONCURRENCY_LEVEL ConcurrencyLevel::NONE
#include "GeneralTest.h"
#undef TEST_METHOD_NAME
#undef LOG_CONCURRENCY_LEVEL
}