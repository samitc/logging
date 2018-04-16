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
            ProcessDataPattern() = default;
            ~ProcessDataPattern() = default;
            IData* getPattern() const override;
        private:
        };
    }
}
#endif