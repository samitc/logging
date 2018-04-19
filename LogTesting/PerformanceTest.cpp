#include <chrono>
#include "../Log/Logger.h"
#include "../Log/XmlLogger.h"
#include <iostream>
#include "gtest/gtest.h"
using namespace Sys::Logging;
namespace LogTesting {
    TEST(PerformanceTest, LogLoadTest) {
        XmlLogger xml;
        xml.load("Log.config");
        Logger log(xml, 0,ConcurrencyLevel::ALL);
        constexpr int NUM_OF_MSG = 20000;
        const char *msg1 = "it is a test";
        const char *msg2 = "and is going to success";
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < NUM_OF_MSG / 4; i++) {
            log.info(msg1);
            log.log(6, msg2);
            log.debug(msg1);
            log.log("info", msg2);
        }
        auto end = std::chrono::high_resolution_clock::now();
#if !defined(NDEBUG)
        constexpr double msgPerMilisec = 10;
#else
        constexpr double msgPerMilisec = 17;
#endif
        double diff = std::chrono::duration<double, std::milli>(end - start).count();
        std::string error;
        error.append("Log load test.\ntook: ");
        error.append(std::to_string(diff));
        error.append(" milisecond to complete.\nthe freq was: ");
        error.append(std::to_string(NUM_OF_MSG / diff));
        std::cout << error.c_str() << std::endl;
        ASSERT_TRUE((double) NUM_OF_MSG / diff > msgPerMilisec);
    }

    TEST(PerformanceTest, LogDelayTest) {
        XmlLogger xml;
        xml.load("Log.config");
        Logger log(xml, 0,ConcurrencyLevel::ALL);
        constexpr int NUM_OF_MSG = 20000;
        const char *msg1 = "it is a test";
        const char *msg2 = "and is going to success";
        auto sum = std::chrono::high_resolution_clock::duration::zero();
        for (size_t i = 0; i < NUM_OF_MSG / 4; i++) {
            auto a = std::chrono::high_resolution_clock::now();
            log.info(msg1);
            auto b = std::chrono::high_resolution_clock::now();
            sum += b - a;
            a = std::chrono::high_resolution_clock::now();
            log.log(6, msg2);
            b = std::chrono::high_resolution_clock::now();
            sum += b - a;
            a = std::chrono::high_resolution_clock::now();
            log.debug(msg1);
            b = std::chrono::high_resolution_clock::now();
            sum += b - a;
            a = std::chrono::high_resolution_clock::now();
            log.log("info", msg2);
            b = std::chrono::high_resolution_clock::now();
            sum += b - a;
        }
#if !defined(NDEBUG)
        constexpr double delayInMili = 0.1;
#else
        constexpr double delayInMili = 0.05;
#endif
        std::string error;
        error.append("Log delay test.\nthe delay is: ");
        error.append(std::to_string(std::chrono::duration<double, std::milli>(sum).count() / NUM_OF_MSG));
        std::cout << error.c_str() << std::endl;
        ASSERT_TRUE((std::chrono::duration<double, std::milli>(sum).count() / NUM_OF_MSG) < delayInMili);
    }
}