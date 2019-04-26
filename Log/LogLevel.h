#ifndef _LOGLEVEL_H_
#define _LOGLEVEL_H_
#include "IData.h"
namespace Sys
{
    namespace Logging
    {
        class PatternData;
        class LogLevel :public IData
        {
        public:
            static UTF8* levelStr;
            LogLevel() = default;
            ~LogLevel() = default;
            virtual UTF8 * getData(const UTF8 * pattern) const;
        private:

        };
    }
}
#endif