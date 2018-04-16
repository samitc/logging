#ifndef _CONSOLEWRITER_H_
#define _CONSOLEWRITER_H_
#include "ILoggerWriter.h"
#include "GlobalDefinitions.h"
namespace Sys
{
    namespace Logging
    {
        class ConsoleWriter :public ILoggerWriter
        {
        public:
            void write(const char* text) const override;
        };
    }
}
#endif