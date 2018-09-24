#ifndef _LOGGERLISTENER_H_
#define _LOGGERLISTENER_H_
#if defined(WINDOWS)
#include <winsock.h>
#elif defined(LINUX)
#endif
#include <queue>
#include <future>
class LoggerListener
{
public:
    LoggerListener(int port);
    ~LoggerListener();
    char* popMessage();
private:
#if defined(WINDOWS)
    SOCKET s;
#elif defined(LINUX)
    int s;
#endif
    const char* addr = "127.0.0.1";
    int port;
    std::queue<char*> message;
    std::future<void> readAsync;
};
#endif