#ifndef _ILOGGERWRITER_H_
#define _ILOGGERWRITER_H_
#include "GlobalDefinitions.h"
namespace Sys
{
    namespace Logging
    {
        struct StreamParam;
        class ILoggerWriter
        {
        public:
            virtual bool compare(const StreamParam&) const = 0;
            virtual void write(const char* text) const = 0;
            virtual ~ILoggerWriter() = 0;
        };
    }
}
#endif