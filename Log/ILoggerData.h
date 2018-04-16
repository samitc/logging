#ifndef _ILOGGER_H_
#define _ILOGGER_H_
#include <vector>
#include "GlobalDefinitions.h"
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
            enum class StreamType
            {
                NONE = 0, FILE = 1, NETWORK, CONSOLE
            };
            struct StreamParam
            {
                StreamType streamType;
                StreamParam() = default;
                StreamParam(const StreamParam&);
                StreamParam& operator=(const StreamParam&);
                ~StreamParam();
                union
                {
                    struct FileParam
                    {
                        UTF8* fileName;
                        bool appendToFile;
                        int maxFiles;
                    } fileParam;
                    struct NetworkParam
                    {
                        char *addr;
                        unsigned short port;
                        Protocol protocol;
                    } networkParam;
                };
                ILoggerWriter* getLoggerWriter() const;
            };
            struct CustomLevel
            {
                String name;
                int level;
            };
            virtual ~ILoggerData() = 0;
            virtual int getNumOfLoggers() const = 0;
            virtual std::vector<CustomLevel> getCustomLevel() const = 0;
            virtual StreamParam getStreams(int loggerNumber) const = 0;
            virtual String getLoggerName(int loggerNumber) const = 0;
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