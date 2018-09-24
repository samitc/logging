#include "gtest/gtest.h"
#include <thread>
#include "../Log/Logger.h"
#include "../Log/LoggerData.h"
#include "../Log/NetworkWriter.h"
#include "../Log/CharUtilities.h"
#include "LoggerListener.h"
using namespace Sys::Logging;
namespace LogTesting 
{
    namespace
    {
#define LOGGER_PORT 2000
        static LoggerData createLoggerData()
        {
            LoggerData logData;
            logData.setLevel(String("45"));
            logData.addCustomLevel(String("fatal"), 1);
            logData.addCustomLevel(String("info"), 30);
            logData.addCustomLevel(String("error"), 10);
            logData.addCustomLevel(String("warn"), 20);
            logData.addCustomLevel(String("trace"), 50);
            logData.addCustomLevel(String("debug"), 40);
            logData.setLoggerName(String("logger"));
            logData.setPatterens("@[msg]");
            ILoggerData::StreamParam sp;
            sp.streamType = ILoggerData::StreamType::NETWORK;
            sp.networkParam.addr = createStr("127.0.0.1");
            sp.networkParam.port = LOGGER_PORT;
            sp.networkParam.protocol = Protocol::UDP;
            logData.setStreamParam(sp);
            return logData;
        }
        static LoggerData logData = createLoggerData();
    }
    TEST(LoggerTest, testLevelFilter)
    {
        LoggerListener listen(LOGGER_PORT);
        Logger logger(logData, 0, 0);
        logger.trace("test");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_EQ(nullptr, listen.popMessage());
    }
    TEST(LoggerTest, testLevel)
    {
        LoggerListener listen(LOGGER_PORT);
        Logger logger(logData, 0, 0);
        logger.debug("test");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        char *ret = listen.popMessage();
        EXPECT_STREQ("test\n", ret);
        delete[] ret;
    }
}