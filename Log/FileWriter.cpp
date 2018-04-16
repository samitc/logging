#include "FileWriter.h"
#include <locale>
#include <codecvt>
namespace Sys
{
    namespace Logging
    {
        FileWriter::FileWriter(const UTF8* path, bool append)
        {
            std::ios_base::openmode mode = 0;
            if (append)
            {
                mode |= std::ios_base::app;
            }
            file = new std::ofstream(path, mode);
        }
        void FileWriter::write(const char * text) const
        {
            file->write(text, strlen(text));
        }
        FileWriter::~FileWriter()
        {
            delete this->file;
        }
    }
}