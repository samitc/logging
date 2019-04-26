#ifndef _DATETIMEPATTERN_H_
#define _DATETIMEPATTERN_H_
#include "BasePattern.h"
namespace Sys
{
    namespace Logging
    {
        class DateTimePattern :public BasePattern
        {
        public:
            DateTimePattern() = default;
            ~DateTimePattern() = default;
            IData* getPattern() const override;
            static bool toDelete();
        private:

        };
    }
}
#endif