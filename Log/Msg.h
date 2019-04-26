#ifndef _MSG_H_
#define _MSG_H_
#include "IData.h"
namespace Sys
{
    namespace Logging
    {
        class PatternData;
        class Msg :public IData
        {
        public:
            static UTF8* msgStr;
            virtual UTF8 * getData(const UTF8 * pattern) const;
        };
    }
}
#endif