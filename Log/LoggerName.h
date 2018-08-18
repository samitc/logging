#ifndef _LOGGERNAME_H_
#define _LOGGERNAME_H_
#include"IData.h"
#include "GlobalDefinitions.h"
#include "LString.h"
namespace Sys
{
    namespace Logging
    {
        class PatternData;
        class LoggerName :public IData
        {
        public:
            explicit LoggerName(const String&);
            virtual UTF8 * getData(const UTF8 * pattern) const;
            int getNumber() const override;
        private:
            String loggerName;
        };
    }
}
#endif