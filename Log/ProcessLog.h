#ifndef _PROCESSLOG_H_
#define _PROCESSLOG_H_
#include <thread>
#include "GlobalDefinitions.h"
#include "Queue.h"
namespace Sys
{
    namespace Logging
    {
        class LogData;
        class String;
        enum class ConcurrencyLevel;
        class ProcessLog
        {
        public:
            ProcessLog() = default;
            ProcessLog(const ProcessLog&) = default;
            ~ProcessLog() = default;
            bool processLog(const LogData &,String &) const;
        private:
        };
    }
}
#endif