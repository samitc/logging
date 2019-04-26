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
            ProcessNamePattern();
            ~ProcessNamePattern();
            IData* getPattern() const override;
            static bool toDelete();
        private:
            IData* cacheProcessName;
        };
    }
}
#endif