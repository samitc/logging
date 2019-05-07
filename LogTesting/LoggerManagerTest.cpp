#include "gtest/gtest.h"
#include <future>
#include "../Log/LoggerManager.h"
#include "../Log/Configuration.h"
#include "../Log/CharUtilities.h"
#include "../Log/LogFilter.h"
#include "NetworkWriterMock.h"
#include "LoggerListener.h"
using namespace Sys::Logging;
namespace LogTesting
{
    namespace
    {
#define LOGGER_PORT 2000
#define sendLog(c,msg) (c)->addRef();manager.log((c), "debug", createStr(msg), "", false);
#define expectStr(msg) do {logMessage=listener.popMessage();} while(logMessage==nullptr);EXPECT_STREQ(msg,logMessage);delete[] logMessage;
        TEST(LoggerManagerTest, testSlowPrinterBug)
        {
            LoggerListener listener(LOGGER_PORT);
            NetworkWriterMock nw("127.0.0.1", LOGGER_PORT, Protocol::UDP);
            {
                LoggerManager manager(2);
                std::atomic_bool isFinished(false);
                auto timeoutThread = std::thread([&isFinished]() {
                    std::this_thread::sleep_for(std::chrono::seconds(10));
                    if (!isFinished)
                    {
                        exit(1);
                    }
                });
                PreMessage* pm1 = new PreMessage("@[msg]", "");
                PreMessage* pm2 = new PreMessage("@[msg]", "");
                LogFilter filter;
                std::atomic<int> numOfArrive(0);
                filter.setFilterFunction([&numOfArrive](const auto&str) {
                    numOfArrive++;
                    while (numOfArrive < 2);
                    if (str == "2")
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(25));
                    }
                    return true;
                });
                Configuration* c = new Configuration(pm1, &nw, 255, std::map<String, int>(), std::vector<String>(), LogFilter(), 0);
                Configuration* c1 = new Configuration(pm2, &nw, 255, std::map<String, int>(), std::vector<String>(), std::move(filter), 2);
                c->clearRemoveWriter();
                c1->clearRemoveWriter();
                nw.setOneWriteSleep(std::chrono::milliseconds(100));
                std::atomic<bool> startWrite(false);
                nw.setCallbackBeforeWrite([&startWrite]() {
                    startWrite = true;
                });
                sendLog(c1, "1");
                sendLog(c1, "2");
                while (!startWrite);
                sendLog(c, "3");
                sendLog(c, "4");
                sendLog(c, "5");
                isFinished = true;
                c1->removeRef();
                c->removeRef();
                timeoutThread.detach();
            }
            char* logMessage;
            expectStr("1\n");
            expectStr("2\n");
            expectStr("3\n");
            expectStr("4\n");
            expectStr("5\n");
            EXPECT_EQ(nullptr, listener.popMessage());
        }
    }
}