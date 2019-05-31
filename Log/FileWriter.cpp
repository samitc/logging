#include "FileWriter.h"
#include <locale>
#include "CharUtilities.h"
#include "StreamParams.h"
namespace Sys
{
    namespace Logging
    {
        FileWriter::FileWriter(const UTF8* path, bool append) :fileName(path)
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
        bool FileWriter::compare(const StreamParam&par) const
        {
            return par.streamType == StreamType::FILE && fileName == par.fileParam.fileName && par.fileParam.appendToFile;
        }
        FileWriter::~FileWriter()
        {
            delete this->file;
        }
    }
}
