#include "BasePattern.h"
namespace Sys
{
    namespace Logging
    {
        void BasePattern::prepeareLogger()
        {
        }
        void BasePattern::setPattern(const std::list<BasePattern*>* patt)
        {
            patterns = patt;
        }
    }
}