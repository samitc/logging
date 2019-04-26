#ifndef _LOGLEVELPATTERN_H_
#define _LOGLEVELPATTERN_H_
#include "BasePattern.h"
namespace Sys
{
    namespace Logging
    {
        class LogLevelPattern :public BasePattern
        {
        public:
            LogLevelPattern() = default;
            ~LogLevelPattern() = default;
            IData* getPattern() const override;
            static bool toDelete();
        private:
        };
    }
}
#endif