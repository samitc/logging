#ifndef _DATETIME_H_
#define _DATETIME_H_
#include "IData.h"
#include <chrono>
#include <list>
#include "TString.h"
namespace Sys
{
    namespace Logging
    {
        class PatternData;
        class DateTime :public IData
        {
        public:
            DateTime();
            ~DateTime() = default;
            const UTF8 * getData(const UTF8 * pattern) const;
        protected:
            std::chrono::time_point<std::chrono::system_clock> time;
        private:
            mutable TString<50> date;
        };
    }
}
#endif
