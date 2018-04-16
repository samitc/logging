#ifndef _LOGGERNAMEPATTERN_H_
#define _LOGGERNAMEPATTERN_H_
#include "BasePattern.h"
#include "GlobalDefinitions.h"
namespace Sys
{
    namespace Logging
    {
        class LoggerNamePattern :public BasePattern
        {
        public:
            LoggerNamePattern() = delete;
            explicit LoggerNamePattern(String&& loggerName);
            ~LoggerNamePattern() = default;
            IData* getPattern() const override;
        private:
            String loggerName;
        };
    }
}
#endif