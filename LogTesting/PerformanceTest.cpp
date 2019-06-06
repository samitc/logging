#include <chrono>
#include "../Log/Logger.h"
#include "../Log/XmlLogger.h"
#include "../Log/LoggerData.h"
#include <iostream>
#include "gtest/gtest.h"
#include "NetworkWriterMock.h"
using namespace Sys::Logging;
namespace LogTesting {
    const char* findMessage(const char* message)
    {
        const char* toFind = "message is: ";
        std::string str(message);
        int loc = str.find(toFind) + strlen(toFind);
        return message + loc;
    }
#define TEST_LOAD_METHOD_NAME    LogLoadMaxConcurrencyTest
#define TEST_DELAY_METHOD_NAME    LogDelayMaxConcurrencyTest
#define TEST_WRITE_DELAY_METHOD_NAME LogWriteDelayMaxConcurrencyTest
#define LOG_CONCURRENCY_LEVEL   ConcurrencyLevel::ALL
#if !defined(NDEBUG)
#define LOAD_THRESHOLD  10
#define DELAY_THRESHOLD 0.1
#define WRITE_DELAY_THRESHOLD 1000
#else
#define LOAD_THRESHOLD  17
#define DELAY_THRESHOLD 0.05
#define WRITE_DELAY_THRESHOLD 500
#endif
#include "PerformanceTest.h"
#undef TEST_LOAD_METHOD_NAME
#undef TEST_DELAY_METHOD_NAME
#undef TEST_WRITE_DELAY_METHOD_NAME
#undef LOG_CONCURRENCY_LEVEL
#undef LOAD_THRESHOLD
#undef DELAY_THRESHOLD
#undef WRITE_DELAY_THRESHOLD
#define TEST_LOAD_METHOD_NAME    LogLoadMinConcurrencyTest
#define TEST_DELAY_METHOD_NAME    LogDelayMinConcurrencyTest
#define TEST_WRITE_DELAY_METHOD_NAME LogWriteDelayMinConcurrencyTest
#define LOG_CONCURRENCY_LEVEL   ConcurrencyLevel::ONE
#if !defined(NDEBUG)
#define LOAD_THRESHOLD  10
#define DELAY_THRESHOLD 0.1
#define WRITE_DELAY_THRESHOLD 1000
#else
#define LOAD_THRESHOLD  17
#define DELAY_THRESHOLD 0.05
#define WRITE_DELAY_THRESHOLD 500
#endif
#include "PerformanceTest.h"
#undef TEST_LOAD_METHOD_NAME
#undef TEST_DELAY_METHOD_NAME
#undef TEST_WRITE_DELAY_METHOD_NAME
#undef LOG_CONCURRENCY_LEVEL
#undef LOAD_THRESHOLD
#undef DELAY_THRESHOLD
#undef WRITE_DELAY_THRESHOLD
#define TEST_LOAD_METHOD_NAME    LogLoadNoneConcurrencyTest
#define TEST_DELAY_METHOD_NAME    LogDelayNoneConcurrencyTest
#define TEST_WRITE_DELAY_METHOD_NAME LogWriteDelayNoneConcurrencyTest
#define LOG_CONCURRENCY_LEVEL   ConcurrencyLevel::NONE
#if !defined(NDEBUG)
#define LOAD_THRESHOLD  10
#define DELAY_THRESHOLD 0.1
#define WRITE_DELAY_THRESHOLD 0.1
#else
#define LOAD_THRESHOLD  17
#define DELAY_THRESHOLD 0.05
#define WRITE_DELAY_THRESHOLD 500
#endif
#include "PerformanceTest.h"
#undef TEST_LOAD_METHOD_NAME
#undef TEST_DELAY_METHOD_NAME
#undef TEST_WRITE_DELAY_METHOD_NAME
#undef LOG_CONCURRENCY_LEVEL
#undef LOAD_THRESHOLD
#undef DELAY_THRESHOLD
#undef WRITE_DELAY_THRESHOLD
}