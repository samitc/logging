#ifndef _LOGMANAGER_H_
#define _LOGMANAGER_H_
#include "GlobalDefinitions.h"
#include <functional>
#include <atomic>
#include <vector>
#include "ProcessLog.h"
#include "OutputProcess.h"
#include "Queue.h"
namespace Sys
{
    namespace Logging
    {
        class Configuration;
        enum class ConcurrencyLevel;
        class LoggerManager
        {
        public:
            LoggerManager(ConcurrencyLevel);
            LoggerManager(int numOfThreads);
            LoggerManager(LoggerManager&&);
            ~LoggerManager();
            void log(Configuration *config, const UTF8 *level, const UTF8 *msg, const UTF8 *name, bool writeImmediately) const;
            void log(Configuration *config, const UTF8 *level, const std::function<UTF8*()>&, const UTF8 *name, bool writeImmediately) const;
        private:
            void printAllToOutput();
            void addToOutput(const LogData*) const;
            void printerWorker();
            void processWorker();
            void log(LogData* logData) const;
            ProcessLog processLog;
            OutputProcess outputProcess;
            std::atomic<bool> isExit;
            mutable std::atomic<uint64_t> logNumber;
            mutable Ccons::Queue<LogData> pData;
            mutable Ccons::Queue<LogData> ipData;
            mutable Ccons::Queue<LogOutput> oData;
            std::vector<std::thread> workerThreads;
            std::atomic_flag isOutputRun;
        };
    }
}
#endif
