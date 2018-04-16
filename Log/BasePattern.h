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
            virtual void prepeareLogger();
            void setPattern(const std::list<BasePattern*>* patt);
        protected:
            const std::list<BasePattern*>* patterns;
        };
    }
}
#endif