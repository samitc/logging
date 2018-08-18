#ifndef _OUTPUTPROCESS_H_
#define _OUTPUTPROCESS_H_
#include <set>
#include <stdint.h>
#include "GlobalDefinitions.h"
namespace Sys
{
    namespace Logging
    {
        class Logger;
        class Configuration;
        struct LogOutput
        {
            LogOutput() = delete;
            LogOutput(const LogOutput&);
            LogOutput(Configuration* config, const UTF8* msg, bool shouldWriteInstantly, uint64_t logNumber);
            LogOutput(LogOutput&&);
            ~LogOutput();
            Configuration* config;
            const UTF8* msg;
            bool shouldWriteInstantly;
            uint64_t logNumber;
            bool operator<(const LogOutput &o) const
            {
                return logNumber < o.logNumber;
            }
        };
        // does not support multithreading. only single thread.
        class OutputProcess
        {
        public:
            explicit OutputProcess();
            ~OutputProcess();
            void outputLog(const LogOutput &) const;
        private:
            void printAllData() const;
            mutable std::set<LogOutput> data;
            mutable long curPrinted;
        };
    }
}
#endif