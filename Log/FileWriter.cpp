#include "FileWriter.h"
#include <locale>
namespace Sys
{
    namespace Logging
    {
        FileWriter::FileWriter(const UTF8* path, bool append)
        {
            std::ios_base::openmode mode = std::ios_base::out;
            if (append)
            {
                mode |= std::ios_base::ate;
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
