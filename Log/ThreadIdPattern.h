#ifndef _THREADIDPATTERN_H_
#define _THREADIDPATTERN_H_
#include "BasePattern.h"
namespace Sys
{
    namespace Logging
    {
        class ThreadIdPattern :public BasePattern
        {
        public:
            ThreadIdPattern() = default;
            ~ThreadIdPattern() = default;
            IData* getPattern() const override;
            static bool toDelete();
        private:
        };
    }
}
#endif