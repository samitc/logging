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
#include "LString.h"
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
            Logger(const ILoggerData &logger, int loggerNumber, ConcurrencyLevel level = ConcurrencyLevel::MEDIUM);
            Logger(const ILoggerData &logger, int loggerNumber, const String &name, ConcurrencyLevel level = ConcurrencyLevel::MEDIUM);
            Logger(const ILoggerData &logger, int loggerNumber, int concurrencyLevel);
            Logger(const ILoggerData &logger, int loggerNumber, const String &name, int concurrencyLevel);
            Logger(const Logger&) = delete;
            Logger(Logger&&);
            virtual ~Logger();
            void log(const char* level, const UTF8* msg, String &name, bool writeImmediately) const;
            void log(unsigned short level, const UTF8 * msg) const;
            void log(const String &level, const UTF8 *msg) const;
            void log(const char * level, const UTF8 *msg) const;
            void log(const char * level, const UTF8 *msg, const String& name) const;
            void log(const char * level, const UTF8 *msg, bool writeImmediately) const;
            void log(unsigned short level, const std::function<String()>&) const;
            void log(const String &level, const std::function<String()>&) const;
            void log(const char * level, const std::function<String()>&) const;
            void log(const char * level, const std::function<String()>&, const String& name) const;
            void log(const char * level, const std::function<String()>&, bool writeImmediately) const;
            void debug(const UTF8 *msg) const;
            void fatal(const UTF8* msg) const;
            void error(const UTF8* msg) const;
            void info(const UTF8* msg) const;
            void warn(const UTF8* msg) const;
            void trace(const UTF8* msg) const;
            void debug(const UTF8 *msg, bool writeImmediately) const;
            void fatal(const UTF8* msg, bool writeImmediately) const;
            void error(const UTF8* msg, bool writeImmediately) const;
            void info(const UTF8* msg, bool writeImmediately) const;
            void warn(const UTF8* msg, bool writeImmediately) const;
            void trace(const UTF8* msg, bool writeImmediately) const;
            void debug(const UTF8 *msg, const String& name) const;
            void fatal(const UTF8* msg, const String& name) const;
            void error(const UTF8* msg, const String& name) const;
            void info(const UTF8* msg, const String& name) const;
            void warn(const UTF8* msg, const String& name) const;
            void trace(const UTF8* msg, const String& name) const;
            void setLogFilter(const LogFilter & logFilter);
            void reloadConfig(const ILoggerData &logger, int loggerNumber);
            LogFilter getLogFilter() const;
        protected:
            explicit Logger(ConcurrencyLevel level);
            explicit Logger(int concurrencyLevel);
        private:
            bool checkLevel(unsigned int level) const;
            void log(unsigned int, const UTF8 *, const String&, const String&, bool) const;
            String name;
            // configuration for the logger. once a log has been started with specific configuration it will stay with the same until the end even if meantime the logger configuration would change.
            std::atomic<Configuration*> config;
            LoggerManager loggerManager;
            mutable std::atomic<uint64_t> logNumber;
            UTF8* fileName;
        };
    }
}
#endif