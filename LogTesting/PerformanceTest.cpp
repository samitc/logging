#include <chrono>
#include "../Log/Logger.h"
#include "../Log/XmlLogger.h"
#include <iostream>
#include "gtest/gtest.h"
using namespace Sys::Logging;
namespace LogTesting {
#define TEST_LOAD_METHOD_NAME    LogLoadMaxConcurrencyTest
#define TEST_DELAY_METHOD_NAME    LogDelayMaxConcurrencyTest
#define LOG_CONCURRENCY_LEVEL   ConcurrencyLevel::ALL
#if !defined(NDEBUG)
#define LOAD_THRESHOLD  10
#define DELAY_THRESHOLD 0.1
#else
#define LOAD_THRESHOLD  17
#define DELAY_THRESHOLD 0.05
#endif
#include "PerformanceTest.h"
#undef TEST_LOAD_METHOD_NAME
#undef TEST_DELAY_METHOD_NAME
#undef LOG_CONCURRENCY_LEVEL
#undef LOAD_THRESHOLD
#undef DELAY_THRESHOLD
#define TEST_LOAD_METHOD_NAME    LogLoadMinConcurrencyTest
#define TEST_DELAY_METHOD_NAME    LogDelayMinConcurrencyTest
#define LOG_CONCURRENCY_LEVEL   ConcurrencyLevel::ONE
#if !defined(NDEBUG)
#define LOAD_THRESHOLD  10
#define DELAY_THRESHOLD 0.1
#else
#define LOAD_THRESHOLD  17
#define DELAY_THRESHOLD 0.05
#endif
#include "PerformanceTest.h"
#undef TEST_LOAD_METHOD_NAME
#undef TEST_DELAY_METHOD_NAME
#undef LOG_CONCURRENCY_LEVEL
#undef LOAD_THRESHOLD
#undef DELAY_THRESHOLD
#define TEST_LOAD_METHOD_NAME    LogLoadNoneConcurrencyTest
#define TEST_DELAY_METHOD_NAME    LogDelayNoneConcurrencyTest
#define LOG_CONCURRENCY_LEVEL   ConcurrencyLevel::NONE
#if !defined(NDEBUG)
#define LOAD_THRESHOLD  10
#define DELAY_THRESHOLD 0.1
#else
#define LOAD_THRESHOLD  17
#define DELAY_THRESHOLD 0.05
#endif
#include "PerformanceTest.h"
#undef TEST_LOAD_METHOD_NAME
#undef TEST_DELAY_METHOD_NAME
#undef LOG_CONCURRENCY_LEVEL
#undef LOAD_THRESHOLD
#undef DELAY_THRESHOLD
}