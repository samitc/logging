#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_
#include <map>
#include <atomic>
#include "GlobalDefinitions.h"
#include "PreMessage.h"
#include "ILoggerWriter.h"
#include "LogFilter.h"
#include "MultipleReadOneWriteLock.h"
namespace Sys
{
    namespace Logging
    {
        class Configuration
        {
        public:
            Configuration();
            Configuration(Configuration&&);
            Configuration(PreMessage*, ILoggerWriter *, unsigned char, std::map<String, int>&&, std::vector<String> &&, LogFilter&&,int);
            ~Configuration();
            const PreMessage* getSysData() const;
            const ILoggerWriter* getLoggerWriter() const;
            unsigned char getLevel() const;
            const std::map<String, int> &getLevels() const;
            const std::vector<String> &getImmLevels() const;
            int getMaxWaitingLogs() const;
            const LogFilter &startUsingFilter() const;
            void endUsingFilter() const;
            void setFilter(const LogFilter& filter);
            Configuration* addRef();
            void removeRef();
            void clearRemoveWriter();
        private:
            PreMessage * sysData;
            ILoggerWriter *loggerWriter;
            unsigned char level;
            std::map<String, int> levels;
            std::vector<String> immLevels;
            LogFilter filter;
            mutable Ccons::MultipleReadOneWriteLock filterRWL;
            std::atomic<unsigned int> numOfRef;
            bool removeWriter;
            int maxWaitingLogs;
        };
    }
}
#endif