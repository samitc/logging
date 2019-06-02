#ifndef _STREAMPARAMS_H_
#define _STREAMPARAMS_H_
#include <vector>
#include "GlobalDefinitions.h"
#include "LString.h"
namespace Sys
{
    namespace Logging
    {
        class ILoggerWriter;
        enum class Protocol;
        enum class StreamType
        {
            NONE = 0, FILE = 1, NETWORK, CONSOLE
        };
        struct FileParam
        {
            UTF8* fileName;
            bool appendToFile;
            int maxFiles;
        };
        struct NetworkParam
        {
            char* addr;
            unsigned short port;
            Protocol protocol;
        };
        struct StreamParam
        {
            StreamType streamType;
            StreamParam() = default;
            StreamParam(const StreamParam&);
            StreamParam& operator=(const StreamParam&);
            ~StreamParam();
            union
            {
                FileParam fileParam;
                NetworkParam networkParam;
                ILoggerWriter* customWriter;
            };
            ILoggerWriter* getLoggerWriter() const;
        };
    }
}
#endif
