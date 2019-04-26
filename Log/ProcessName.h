#ifndef _PROCESSNAME_H_
#define _PROCESSNAME_H_
#include "IData.h"
#include <cstdio>
namespace Sys
{
    namespace Logging
    {
        class PatternData;
        class ProcessName :public IData
        {
        public:
            ProcessName();
            UTF8* getData(const UTF8 * pattern) const override;
        private:
            static CONSTEXPRN int BUFFER_SIZE = FILENAME_MAX;
            UTF8 name[BUFFER_SIZE];
        };
    }
}
#endif