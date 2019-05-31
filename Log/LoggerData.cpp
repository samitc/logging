#include "LoggerData.h"
#include "LogFilter.h"
#include "StreamParams.h"
namespace Sys
{
    namespace Logging
    {
        LoggerData::LoggerData() :param()
        {
        }
        LoggerData::~LoggerData()
        {
        }
        int LoggerData::getNumOfLoggers() const
        {
            return 1;
        }
        StreamParam LoggerData::getStreams(int loggerNumber) const
        {
            return param;
        }
        size_t LoggerData::getMaxLogSize(int loggerNumber) const
        {
            return maxLogSizeInKB;
        }
        std::vector<ILoggerData::CustomLevel> LoggerData::getCustomLevel() const
        {
            return customLevels;
        }
        unsigned int LoggerData::getMaxLogTime(int loggerNumber) const
        {
            return maxLogTimeInSec;
        }
        String LoggerData::getLoggerName(int loggerNumber) const
        {
            return logName;
        }
        String LoggerData::getPaterens(int loggerNumber) const
        {
            return pat;
        }
        String LoggerData::getLevel(int loggerNumber) const
        {
            return level;
        }
        int LoggerData::getMaxWaitingLogs(int loggerNumber) const
        {
            return -1;
        }
        LogFilter LoggerData::getLogFilter(int loggerNumber) const
        {
            return LogFilter();
        }
        std::vector<String> LoggerData::getImmediateLevels(int loggerNumber) const
        {
            return std::vector<String>();
        }
        void LoggerData::setLevel(const String& level)
        {
            this->level = level;
        }
        void LoggerData::setPatterens(const UTF8 * pat)
        {
            this->pat = pat;
        }
        void LoggerData::setPatterens(const String & pat)
        {
            this->pat = pat;
        }
        void LoggerData::setPatterens(String && pat)
        {
            this->pat = std::move(pat);
        }
        void LoggerData::setLoggerName(const UTF8 * name)
        {
            logName = name;
        }
        void LoggerData::setLoggerName(const String & name)
        {
            logName = name;
        }
        void LoggerData::setLoggerName(String && name)
        {
            logName = std::move(name);
        }
        void LoggerData::setStreamParam(const StreamParam & stream)
        {
            this->param = stream;
        }
        void LoggerData::setStreamParam(StreamParam && stream)
        {
            param = std::move(stream);
        }
        void LoggerData::setMaxLogSizeInKB(size_t size)
        {
            maxLogSizeInKB = size;
        }
        void LoggerData::setMaxLogTimeInSec(unsigned int time)
        {
            maxLogTimeInSec = time;
        }
        void LoggerData::addCustomLevel(const String &name, int level)
        {
            CustomLevel custom;
            custom.name = name;
            custom.level = level;
            customLevels.push_back(std::move(custom));
        }
    }
}