#include "gtest/gtest.h"
#include <thread>
#include "../Log/LogStatement.h"
#include "../Log/PreMessage.h"
#include "../Log/LString.h"
#include "../Log/ThreadId.h"
using namespace Sys::Logging;
namespace LogTesting 
{
    TEST(LogStatementTest, testUnnecessaryDataThenNecessary)
    {
        ThreadId t;
        PreMessage pm("@[lname](@[llevel]).process data : @[tId].message is : @[msg]", "logname");
        LogStatement ls(&pm, "message", String("test_level"));
        String expectedMsg = String("logname(test_level).process data : ");
        auto tData = t.getData(nullptr);
        expectedMsg.append(tData);
        expectedMsg.append(".message is : message\n");
        auto necessaryData = pm.getNecessaryData();
        EXPECT_STREQ(expectedMsg.c_str(), ls.getMessage(necessaryData).c_str());
        delete []tData;
        for (auto n : necessaryData)
        {
            delete n;
        }
    }
    TEST(LogStatementTest, testPatternTrim)
    {
        PreMessage pm("@[msg].", "logname");
        LogStatement ls(&pm, "message", String("test_level"));
        String expextedMsg = String("message.\n");
        EXPECT_STREQ(expextedMsg.c_str(), ls.getMessage(pm.getNecessaryData()).c_str());
    }
    TEST(LogStatementTest, testNonPatternStart)
    {
        PreMessage pm(".@[msg].", "logname");
        LogStatement ls(&pm, "message", String("test_level"));
        String expextedMsg = String(".message.\n");
        EXPECT_STREQ(expextedMsg.c_str(), ls.getMessage(pm.getNecessaryData()).c_str());
    }
    TEST(LogStatementTest, testPatternOnly)
    {
        PreMessage pm("@[msg]", "logname");
        LogStatement ls(&pm, "message", String("test_level"));
        String expextedMsg = String("message\n");
        EXPECT_STREQ(expextedMsg.c_str(), ls.getMessage(pm.getNecessaryData()).c_str());
    }
    TEST(LogStatementTest, testNonPatternOnly)
    {
        PreMessage pm("pattern", "logname");
        LogStatement ls(&pm, "message", String("test_level"));
        String expextedMsg = String("pattern\n");
        EXPECT_STREQ(expextedMsg.c_str(), ls.getMessage(pm.getNecessaryData()).c_str());
    }
}