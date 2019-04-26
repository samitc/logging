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
            UTF8 * getData(const UTF8 * pattern) const override;
        protected:
            size_t id;
        };
    }
}
#endif