#ifndef _LOGGER_H_
#define _LOGGER_H_
#include "ILoggerData.h"
#include <vector>
namespace Sys
{
    namespace Logging
    {
        class LoggerData :public ILoggerData
        {
        public:
            LoggerData();
            ~LoggerData() override;
            int getNumOfLoggers() const override;
            StreamParam getStreams(int loggerNumber) const override;
            size_t getMaxLogSize(int loggerNumber) const override;
            std::vector<CustomLevel> getCustomLevel() const override;
            unsigned int getMaxLogTime(int loggerNumber) const  override;
            String getLoggerName(int loggerNumber) const override;
            String getPaterens(int loggerNumber) const override;
            String getLevel(int loggerNumber) const override;
            int getMaxWaitingLogs(int loggerNumber) const override;
            LogFilter getLogFilter(int loggerNumber) const override;
            std::vector<String> getImmediateLevels(int loggerNumber) const override;
            void setLevel(const String& level);
            void setPatterens(const UTF8 * pat);
            void setPatterens(const String& pat);
            void setPatterens(String&& pat);
            void setLoggerName(const UTF8* name);
            void setLoggerName(const String& name);
            void setLoggerName(String&& name);
            void setStreamParam(const StreamParam &stream);
            void setStreamParam(StreamParam &&stream);
            void setMaxLogSizeInKB(size_t size);
            void setMaxLogTimeInSec(unsigned int time);
            void addCustomLevel(const String &name,int level);
        private:
            String logName;
            String level;
            StreamParam param;
            String pat;
            size_t maxLogSizeInKB;
            unsigned int maxLogTimeInSec;
            std::vector<CustomLevel> customLevels;
        };
    }
}
#endif