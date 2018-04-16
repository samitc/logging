#ifndef _NETWORKWRITER_H_
#define _NETWORKWRITER_H_
#include "ILoggerWriter.h"
#if defined(WINDOWS)
#include <winsock.h>
#elif defined(LINUX)
#endif
namespace Sys
{
    namespace Logging
    {
        enum class Protocol
        {
            TCP = 1, UDP
        };
        class NetworkWriter :public ILoggerWriter
        {
        public:
            NetworkWriter(const char* addr, unsigned short port, Protocol protocol);
            virtual void write(const char* text) const;
            ~NetworkWriter();
        private:
#if defined(WINDOWS)
            SOCKET s;
#elif defined(LINUX)
            int s;
#endif
            char* addr;
            unsigned short port;
        };
    }
}
#endif