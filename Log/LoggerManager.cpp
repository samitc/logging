#include "LoggerManager.h"
#include <algorithm>

#if defined(LINUX)
#include <climits>

#endif
#include "Configuration.h"
#include "LogData.h"
#include "Logger.h"

namespace Sys
{
    namespace Logging
    {
        int getThreadCount(ConcurrencyLevel level);
        Sys::Logging::LoggerManager::LoggerManager(ConcurrencyLevel level) : LoggerManager(getThreadCount(level))
        {
        }
        LoggerManager::LoggerManager(int numOfThreads)
                : logNumber(0),
                  numberOfWaitingLogs(0),
                  isExit(false),
                  processLog(),
                  outputProcess(),
                  workerThreads(numOfThreads),
                  pData(),
                  ipData(),
                  oData()
        {
            isOutputRun.clear();
            if (numOfThreads > 0) {
                workerThreads[0] = std::thread([&]{ printerWorker(); });
                for (size_t i = 1; i < numOfThreads; i++)
                {
                    workerThreads[i] = std::thread([&]{ processWorker(); });
                }
            }
        }
        LoggerManager::LoggerManager(LoggerManager &&)
        {
        }
        Sys::Logging::LoggerManager::~LoggerManager()
        {
            isExit = true;
            for (size_t i = 0; i < workerThreads.size(); i++)
            {
                pData.enqueue(nullptr);
            }
            for (auto &workers : workerThreads)
            {
                if (workers.joinable())
                {
                    workers.join();
                }
            }
            while (!pData.isEmpty())
            {
                LogData *data = pData.dequeue();
                if (data != nullptr)
                {
                    addToOutput(data);
                    delete data;
                }
            }
            printAllToOutput();
        }
        void Sys::Logging::LoggerManager::log(Configuration *config,
                                              const UTF8 *level,
                                              const UTF8 *msg,
                                              const UTF8 *name,
                                              bool writeImmediately) const
        {
            auto datas = config->getSysData()->getNecessaryData();
            // if should write immediately or the level write immediately
            bool isWriteImmediately = writeImmediately ||
                                      !(std::find_if(config->getImmLevels().cbegin(),
                                                     config->getImmLevels().cend(),
                                                     [level](const String &str) {
                                                         return !strcmp(level, str.c_str());
                                                     }) == config->getImmLevels().cend());
            log(new LogData(config, msg, String(level), String(name), isWriteImmediately, datas, logNumber++));
        }
        void LoggerManager::addToOutput(const LogData *logData) const
        {
            UTF8 *msg = processLog.processLog(*logData);
            if (msg)
            {
                oData.enqueue(new LogOutput(logData->getConfig(),
                                            msg,
                                            logData->getWriteImmediately(),
                                            logData->getLogNumber()));
            }
            else
            {
                logData->getConfig()->removeRef();
            }
        }
        void LoggerManager::printerWorker()
        {
            LogData *data;
            do {
                while (data = ipData.dequeue())
                {
                    addToOutput(data);
                    delete data;
                }
                printAllToOutput();
                data = pData.dequeueW();
                if (data)
                {
                    addToOutput(data);
                    delete data;
                }
            } while (!isExit && data != nullptr);
            printAllToOutput();
        }
        void LoggerManager::processWorker()
        {
            LogData *data;
            do {
                data = pData.dequeueW();
                if (data) {
                    addToOutput(data);
                    delete data;
                }
            } while (!isExit && data != nullptr);
        }
        void Sys::Logging::LoggerManager::log(LogData *logData) const
        {
            if (!workerThreads.size())
            {
                UTF8 *msg = processLog.processLog(*logData);
                if (msg)
                {
                    outputProcess.outputLog(LogOutput(logData->getConfig(),
                                                      msg,
                                                      logData->getWriteImmediately(),
                                                      logData->getLogNumber()));
                }
                else
                {
                    logData->getConfig()->removeRef();
                }
                delete logData;
            }
            else
            {
                while (numberOfWaitingLogs > logData->getConfig()->getMaxWaitingLogs())
                {
                    LogData *data;
                    data = this->pData.dequeue();
                    if (data)
                    {
                        addToOutput(data);
                        delete data;
                    }
                }
                ++numberOfWaitingLogs;
                if (logData->getWriteImmediately())
                {
                    ipData.enqueue(logData);
                    pData.enqueue(nullptr);// to wake up worker thread
                }
                else
                {
                    pData.enqueue(logData);
                }
            }
        }
        void Sys::Logging::LoggerManager::log(Configuration *config,
                                              const UTF8 *level,
                                              const std::function<UTF8 *()> &msg,
                                              const UTF8 *name,
                                              bool writeImmediately) const
        {
            this->log(config, level, msg(), name, writeImmediately);
        }
        void LoggerManager::printAllToOutput()
        {
            if (!oData.isEmpty() && !isOutputRun.test_and_set())
            {
                while (!oData.isEmpty())
                {
                    LogOutput *logOutput = oData.dequeue();
                    outputProcess.outputLog(*logOutput);
                    delete logOutput;
                    --numberOfWaitingLogs;
                }
                isOutputRun.clear();
            }
        }
        int getThreadCount(ConcurrencyLevel level)
        {
            unsigned int hardwareThread = std::thread::hardware_concurrency();
            unsigned int count;
            switch (level)
            {
                case Sys::Logging::ConcurrencyLevel::NONE:count = 0;
                    break;
                case Sys::Logging::ConcurrencyLevel::ONE:count = 1;
                    break;
                case Sys::Logging::ConcurrencyLevel::VERY_LOW:count = hardwareThread / 8 + 1;
                    break;
                case Sys::Logging::ConcurrencyLevel::LOW:count = hardwareThread / 4 + 1;
                    break;
                case Sys::Logging::ConcurrencyLevel::MEDIUM:count = hardwareThread > 3 ? hardwareThread / 2 : 1;
                    break;
                case Sys::Logging::ConcurrencyLevel::HIGH:
                    count = hardwareThread > 4 ? hardwareThread > 6 ? (unsigned int)(hardwareThread /
                                                                                     1.7) : hardwareThread -
                                                                                            2 : 3;
                    break;
                case Sys::Logging::ConcurrencyLevel::VERY_HIGH:
                    count = hardwareThread > 5 ? hardwareThread > 8 ? (unsigned int)(hardwareThread /
                                                                                     1.4) : hardwareThread - 1 : 4;
                    break;
                case Sys::Logging::ConcurrencyLevel::ALL:count = UINT_MAX;
                    break;
            }
            return std::min(count, hardwareThread);
        }
    }
}
