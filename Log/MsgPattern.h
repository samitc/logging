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
            MsgPattern();
            ~MsgPattern();
            IData* getPattern() const override;
            static bool toDelete();
        private:
            IData* cacheMsg;
        };
    }
}
#endif