#ifndef _THREADID_H_
#define _THREADID_H_
#include "IData.h"
#include <stddef.h>
namespace Sys
{
    namespace Logging
    {
        class PatternData;
        class ThreadId :public IData
        {
        public:
            ThreadId();
            const UTF8* getData(const UTF8* pattern) const override;
        protected:
            static const int TS_SIZE = 11;
            size_t id;
            mutable UTF8 ts[TS_SIZE];
        };
    }
}
#endif