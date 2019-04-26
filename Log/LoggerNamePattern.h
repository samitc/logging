#ifndef _LOGGERNAMEPATTERN_H_
#define _LOGGERNAMEPATTERN_H_
#include "BasePattern.h"
#include "GlobalDefinitions.h"
#include "LString.h"
namespace Sys
{
    namespace Logging
    {
        class LoggerNamePattern :public BasePattern
        {
        public:
            LoggerNamePattern() = delete;
            explicit LoggerNamePattern(String&& loggerName);
            ~LoggerNamePattern();
            IData* getPattern() const override;
            static bool toDelete();
        private:
            IData* cacheLoggerName;
            String loggerName;
        };
    }
}
#endif