#include "NetworkWriter.h"
#if defined(WINDOWS)
#pragma comment (lib, "Ws2_32.lib")
#elif defined(LINUX)
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
namespace Sys
{
    namespace Logging
    {
        NetworkWriter::NetworkWriter(const char* addr, unsigned short port, Protocol protocol)
        {
#undef strlen
            register int l = strlen(addr);
            this->addr = new char[l];
            memcpy(this->addr, addr, sizeof(addr));
            this->port = port;
#if defined(WINDOWS)
            WSADATA wsdata;
            int error = WSAStartup(MAKEWORD(2, 2), &wsdata);
            if (error)
            {
                throw "Not implement";
            }
            if (wsdata.wVersion != 0x0202)
            {
                WSACleanup();
                throw "Not implement";
            }
#endif
            int type;
            int proto = 0;
            switch (protocol)
            {
            case Protocol::TCP:
                type = SOCK_STREAM;
#if defined(WINDOWS)
                proto = IPPROTO_TCP;
#endif
                break;
            case Protocol::UDP:
                type = SOCK_DGRAM;
#if defined(WINDOWS)
                proto = IPPROTO_UDP;
#endif
                break;
            }
            s = socket(AF_INET, type, proto);
#if defined(WINDOWS)
            if (s == INVALID_SOCKET)
#elif defined(LINUX)
            if (s < 0)
#endif
            {
                throw "Not implement";
            }
#if defined(WINDOWS)
            SOCKADDR_IN target;
            target.sin_family = AF_INET;
            target.sin_port = htons(port);
            target.sin_addr.s_addr = inet_addr(addr);
            if (connect(s, (SOCKADDR *)&target, sizeof(target)) == INVALID_SOCKET)
#elif defined(LINUX)
            sockaddr_in target;
            target.sin_family = AF_INET;
            target.sin_port = htons(port);
            inet_pton(AF_INET, addr, &target.sin_addr);
            if (connect(s,(sockaddr*)&target,sizeof(target)))
#endif
            {
                throw "Not implement";
            }
        }
        void NetworkWriter::write(const char * text) const
        {
            int sendB = 0;
            int bsend = 0;
            int l = strlen(text) + 1;
            const char *p = text;
            do
            {
                bsend = send(s, p, l - sendB, 0);
                sendB += bsend;
            } while (sendB < l&&bsend != 0);
        }
        NetworkWriter::~NetworkWriter()
        {
#if defined(WINDOWS)
            closesocket(s);
            WSACleanup();
#elif defined(LINUX)
            close(s);
#endif
        }
    }
}