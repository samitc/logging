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
        expectedMsg.append(t.getData(nullptr));
        expectedMsg.append(".message is : message\n");
        EXPECT_STREQ(expectedMsg.c_str(), ls.getMessage(pm.getNecessaryData()).c_str());
    }
    TEST(LogStatementTest, testPatternTrim)
    {
        PreMessage pm("@[msg].", "logname");
        LogStatement ls(&pm, "message", String("test_level"));
        String expextedMsg = String("message.\n");
        EXPECT_STREQ(expextedMsg.c_str(), ls.getMessage(pm.getNecessaryData()).c_str());
    }
}