#ifndef _ILOGGER_H_
#define _ILOGGER_H_
#include <vector>
#include <stdlib.h>
#include "GlobalDefinitions.h"
#include "LString.h"
#include "StreamParams.h"
namespace Sys
{
    namespace Logging
    {
        class ILoggerWriter;
        class LogFilter;
        enum class Protocol;
        class ILoggerData
        {
        public:
            struct CustomLevel
            {
                String name;
                int level;
            };
            virtual ~ILoggerData() = default;
            virtual int getNumOfLoggers() const = 0;
            virtual std::vector<CustomLevel> getCustomLevel() const = 0;
            virtual StreamParam getStreams(int loggerNumber) const = 0;
            virtual String getLoggerName(int loggerNumber) const = 0;
            virtual int getMaxWaitingLogs(int loggerNumber) const = 0;
            virtual String getPaterens(int loggerNumber) const = 0;
            virtual size_t getMaxLogSize(int loggerNumber) const = 0;
            virtual unsigned int getMaxLogTime(int loggerNumber) const = 0;
            virtual String getLevel(int loggerNumber) const = 0;
            virtual LogFilter getLogFilter(int loggerNumber) const = 0;
            virtual std::vector<String> getImmediateLevels(int loggerNumber) const = 0;
        };
    }
}
#endif
