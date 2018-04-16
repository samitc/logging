#ifndef _ILOGGERWRITER_H_
#define _ILOGGERWRITER_H_
#include "GlobalDefinitions.h"
namespace Sys
{
    namespace Logging
    {
        class ILoggerWriter
        {
        public:
            virtual void write(const char* text) const = 0;
            virtual ~ILoggerWriter() = 0;
        };
    }
}
#endif