#ifndef _PROCESSDATAPATTERN_H_
#define _PROCESSDATAPATTERN_H_
#include "BasePattern.h"
namespace Sys
{
    namespace Logging
    {
        class ProcessDataPattern :public BasePattern
        {
        public:
            ProcessDataPattern();
            ~ProcessDataPattern();
            IData* getPattern() const override;
            static bool toDelete();
        private:
            IData* cacheDataProcess;
        };
    }
}
#endif