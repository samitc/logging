#include "gtest/gtest.h"
#include <thread>
#include "../Log/LogStatement.h"
#include "../Log/PreMessage.h"
#include "../Log/LString.h"
#include "../Log/ThreadId.h"
using namespace Sys::Logging;
namespace LogTesting 
{
#define createDatas int datasSize = pm.getNumOfNecessaryData();\
    IndexData* datas = (IndexData*)alloca(datasSize * sizeof(IndexData));\
    pm.getNecessaryData(datas);
#define destroyDatas for (size_t i = 0; i < datasSize; i++){delete datas[i].data;}
#define EXPECT EXPECT_STREQ((expectedMsg).c_str(), (ls).getMessage(datas, datasSize).c_str());
    TEST(LogStatementTest, testUnnecessaryDataThenNecessary)
    {
        ThreadId t;
        String level("test_level");
        PreMessage pm("@[lname](@[llevel]).process data : @[tId].message is : @[msg]", "logname");
        LogStatement ls(&pm, "message", level);
        String expectedMsg = String("logname(test_level).process data : ");
        auto tData = t.getData(nullptr);
        expectedMsg.append(tData);
        expectedMsg.append(".message is : message\n");
        createDatas;
        EXPECT;
        destroyDatas
    }
    TEST(LogStatementTest, testPatternTrim)
    {
        PreMessage pm("@[msg].", "logname");
        LogStatement ls(&pm, "message", String("test_level"));
        String expectedMsg = String("message.\n");
        createDatas;
        EXPECT;
        destroyDatas;
    }
    TEST(LogStatementTest, testNonPatternStart)
    {
        PreMessage pm(".@[msg].", "logname");
        LogStatement ls(&pm, "message", String("test_level"));
        String expectedMsg = String(".message.\n");
        createDatas;
        EXPECT;
        destroyDatas;
    }
    TEST(LogStatementTest, testPatternOnly)
    {
        PreMessage pm("@[msg]", "logname");
        LogStatement ls(&pm, "message", String("test_level"));
        String expectedMsg = String("message\n");
        createDatas;
        EXPECT;
        destroyDatas;
    }
    TEST(LogStatementTest, testNonPatternOnly)
    {
        PreMessage pm("pattern", "logname");
        LogStatement ls(&pm, "message", String("test_level"));
        String expectedMsg = String("pattern\n");
        createDatas;
        EXPECT;
        destroyDatas;
    }
}