#ifndef _XMLLOGGER_H_
#define _XMLLOGGER_H_
#include "ILoggerData.h"
#include <stack>
#include <vector>
#include "GlobalDefinitions.h"
namespace Sys
{
    namespace Logging
    {
        template <class T> class Node;
        class ILoggerWriter;
        class XmlLogger :public ILoggerData
        {
        public:
            XmlLogger();
            ~XmlLogger();
            virtual bool load(const char *fileName);
            int getNumOfLoggers() const override;
            String getLoggerName(int loggerNumber) const override;
            String getPaterens(int loggerNumber) const override;
            std::vector<ILoggerData::CustomLevel> getCustomLevel() const override;
            StreamParam getStreams(int loggerNumber) const override;
            size_t getMaxLogSize(int loggerNumber) const override;
            int getMaxWaitingLogs(int loggerNumber) const override;
            unsigned int getMaxLogTime(int loggerNumber) const override;
            String getLevel(int loggerNumber) const override;
            LogFilter getLogFilter(int loggerNumber) const override;
            std::vector<String> getImmediateLevels(int loggerNumber) const override;
        protected:
        private:
            struct LogData
            {
                LogData() = default;
                LogData(const String &, const String&);
                LogData(String &&, String&&);
                String appenderName;
                String logName;
            };
            int getLogNumber(const String &appender) const;
            void addNewLogger();
            bool nodeScan(Node<UTF8> *node);
            void nodeEnd(Node<UTF8> *node);
            void addImmediateWrite(UTF8* name);
            std::stack<UTF8*> xmlIner;
            int curLogger;
            std::vector<LogData> indexToLoggerNames;
            std::vector<CustomLevel> customLevels;
            std::vector<StreamParam> streams;
            std::vector<String> pat;
            std::vector<String> levels;
            std::vector<size_t> maxLogSizeInKB;
            std::vector<int> maxWaitingLogs;
            std::vector<unsigned int> maxLogTimeInSec;
            std::vector<LogFilter> logsFilter;
            std::vector<std::vector<String>> immLevels;
        };
    }
}
#endif