#include "LoggerListener.h"
#if defined(WINDOWS)
#pragma comment (lib, "Ws2_32.lib")
#elif defined(LINUX)
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <atomic>
namespace
{
#if defined(WINDOWS)
    using SocketTarget = SOCKADDR;
#elif defined(LINUX)
    using SocketTarget = sockaddr;
#endif
    auto createTarget(const char*addr, int port)
    {
#if defined(WINDOWS)
        SOCKADDR_IN targetDesc;
        targetDesc.sin_addr.s_addr = inet_addr(addr);
#elif defined(LINUX)
        sockaddr_in targetDesc;
        inet_pton(AF_INET, addr, &targetDesc.sin_addr);
#endif
        targetDesc.sin_family = AF_INET;
        targetDesc.sin_port = htons(port);
        return targetDesc;
    }
}
LoggerListener::LoggerListener(int port) : port(port)
{
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
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    auto target = createTarget(addr, port);
    bind(s, (SocketTarget*)&target, sizeof(target));
    readAsync = std::async(std::launch::async, [this]
    {
        const int MAX_READ = 4096;
        char readBuf[MAX_READ];
        int actualRead;
        do
        {
            actualRead = recv(s, readBuf, MAX_READ, 0);
            if (actualRead <= 0)
            {
                break;
            }
            char *readed = new char[actualRead];
            strcpy(readed, readBuf);
            message.push(readed);
        } while (true);
    });
}

LoggerListener::~LoggerListener()
{
    auto target = createTarget(addr, port);
    sendto(s, nullptr, 0, 0, (SocketTarget*)&target, sizeof(target));
#if defined(WINDOWS)
    closesocket(s);
    WSACleanup();
#elif defined(LINUX)
    close(s);
#endif
}

char * LoggerListener::popMessage()
{
    if (message.size() == 0)
    {
        return nullptr;
    }
    char *ret = message.front();
    message.pop();
    return ret;
}