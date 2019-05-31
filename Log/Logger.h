#ifndef _LOG_H_
#define _LOG_H_
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include <atomic>
#include "GlobalDefinitions.h"
#include "LogFilter.h"
#include "LoggerManager.h"
namespace Sys
{
    namespace Logging
    {
        using Level = int;
        class ILogStatement;
        class PreMessage;
        class ILoggerWriter;
        class Configuration;
        class ILoggerData;
        enum class ConcurrencyLevel
        {
            NONE,
            ONE,
            VERY_LOW,
            LOW,
            MEDIUM,
            HIGH,
            VERY_HIGH,
            ALL
        };
        class Logger
        {
        public:
            Logger(const ILoggerData& logger, int loggerNumber, ConcurrencyLevel level = ConcurrencyLevel::MEDIUM);
            Logger(const ILoggerData& logger, int loggerNumber, const UTF8* name, ConcurrencyLevel level = ConcurrencyLevel::MEDIUM);
            Logger(const ILoggerData& logger, int loggerNumber, int concurrencyLevel);
            Logger(const ILoggerData& logger, int loggerNumber, const UTF8* name, int concurrencyLevel);
            Logger(const Logger&) = delete;
            Logger(Logger&&);
            virtual ~Logger();
            void log(const UTF8* level, const UTF8* msg, const UTF8* name, bool writeImmediately) const;
            void log(unsigned short level, const UTF8* msg) const;
            void log(const UTF8* level, const UTF8* msg) const;
            void log(const UTF8* level, const UTF8* msg, const UTF8* name) const;
            void log(const UTF8* level, const UTF8* msg, bool writeImmediately) const;
            void log(unsigned short level, const std::function<const UTF8*()>&) const;
            void log(const UTF8* level, const std::function<const UTF8*()>&) const;
            void log(const UTF8* level, const std::function<const UTF8*()>&, const UTF8* name) const;
            void log(const UTF8* level, const std::function<const UTF8*()>&, bool writeImmediately) const;
            void debug(const UTF8* msg) const;
            void fatal(const UTF8* msg) const;
            void error(const UTF8* msg) const;
            void info(const UTF8* msg) const;
            void warn(const UTF8* msg) const;
            void trace(const UTF8* msg) const;
            void debug(const UTF8* msg, bool writeImmediately) const;
            void fatal(const UTF8* msg, bool writeImmediately) const;
            void error(const UTF8* msg, bool writeImmediately) const;
            void info(const UTF8* msg, bool writeImmediately) const;
            void warn(const UTF8* msg, bool writeImmediately) const;
            void trace(const UTF8* msg, bool writeImmediately) const;
            void debug(const UTF8* msg, const UTF8* name) const;
            void fatal(const UTF8* msg, const UTF8* name) const;
            void error(const UTF8* msg, const UTF8* name) const;
            void info(const UTF8* msg, const UTF8* name) const;
            void warn(const UTF8* msg, const UTF8* name) const;
            void trace(const UTF8* msg, const UTF8* name) const;
            void setLogFilter(const LogFilter& logFilter);
            void reloadConfig(const ILoggerData& logger, int loggerNumber);
            LogFilter getLogFilter() const;
        protected:
            explicit Logger(ConcurrencyLevel level);
            explicit Logger(int concurrencyLevel);
        private:
            bool checkLevel(unsigned int level) const;
            void plog(unsigned int, const UTF8*, const UTF8*, const UTF8*, bool) const;
            UTF8* name;
            // configuration for the logger. once a log has been started with specific configuration it will stay with the same until the end even if meantime the logger configuration would change.
            std::atomic<Configuration*> config;
            LoggerManager loggerManager;
            mutable std::atomic<uint64_t> logNumber;
        };
    }
}
#endif