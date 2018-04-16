#ifndef _FILEWRITER_H_
#define _FILEWRITER_H_
#include "ILoggerWriter.h"
#include "GlobalDefinitions.h"
#include <fstream>
namespace Sys
{
    namespace Logging
    {
        class FileWriter :public ILoggerWriter
        {
        public:
            FileWriter(const UTF8* path, bool append);
            void write(const char* text) const override;
            ~FileWriter();
        private:
            std::ofstream *file;
        };
    }
}
#endif