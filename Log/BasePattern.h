#ifndef _BASEPATTERN_H_
#define _BASEPATTERN_H_
#include <list>
namespace Sys
{
    namespace Logging
    {
        class IData;
        class BasePattern
        {
        public:
            BasePattern() = default;
            virtual ~BasePattern() = default;
            virtual IData* getPattern() const = 0;
        };
    }
}
#endif