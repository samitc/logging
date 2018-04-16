#include "LoggerData.h"
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
        ILoggerData::StreamParam LoggerData::getStreams(int loggerNumber) const
        {
            return param;
        }
        size_t LoggerData::getMaxLogSize(int loggerNumber) const
        {
            return maxLogSizeInKB;
        }
        std::vector<ILoggerData::CustomLevel> LoggerData::getCustomLevel() const
        {
            return std::vector<CustomLevel>();
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
    }
}