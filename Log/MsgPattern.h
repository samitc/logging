#ifndef _MSGPATTERN_H_
#define _MSGPATTERN_H_
#include "BasePattern.h"
namespace Sys
{
    namespace Logging
    {
        class MsgPattern :public BasePattern
        {
        public:
            MsgPattern() = default;
            ~MsgPattern() = default;
            IData* getPattern() const override;
        private:
        };
    }
}
#endif