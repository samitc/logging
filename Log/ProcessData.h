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
            virtual UTF8 * getData(const UTF8 * pattern) const;
            int getNumber() const override;
        protected:
            DWORD ID;
        };
    }
}
#endif