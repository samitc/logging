#ifndef _PROCESSDATA_H_
#define _PROCESSDATA_H_
#include "IData.h"
typedef unsigned long       DWORD;
namespace Sys
{
    namespace Logging
    {
        class PatternData;
        class ProcessData :public IData
        {
        public:
            ProcessData();
            const UTF8* getData(const UTF8 * pattern) const;
        protected:
            DWORD ID;
            static const int TS_SIZE = 11;
            mutable UTF8 ts[TS_SIZE];
        };
    }
}
#endif