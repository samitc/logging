#ifndef _PROCESSNAMEPATTERN_H_
#define _PROCESSNAMEPATTERN_H_
#include "BasePattern.h"
namespace Sys
{
    namespace Logging
    {
        class ProcessNamePattern :public BasePattern
        {
        public:
            ProcessNamePattern() = default;
            ~ProcessNamePattern() = default;
            IData* getPattern() const override;
        private:
        };
    }
}
#endif