#ifndef _NETWORKWRITERMOCK_H_
#define _NETWORKWRITERMOCK_H_
#include "../Log/NetworkWriter.h"
#include <chrono>
#include <functional>
using namespace Sys::Logging;
class NetworkWriterMock:public NetworkWriter
{
public:
    NetworkWriterMock(const char* addr, unsigned short port, Protocol protocol);
    ~NetworkWriterMock();
    void write(const char* text) const override;
    template <typename Rep,typename Period> void setOneWriteSleep(const std::chrono::duration<Rep,Period> &duration);
    void setCallbackBeforeWrite(const std::function<void(const char*)> &f);
private:
    mutable std::chrono::nanoseconds oneSleepDuration;
    std::function<void(const char*)> callbackBeforeWrite;
};
#endif
template<typename Rep, typename Period>
inline void NetworkWriterMock::setOneWriteSleep(const std::chrono::duration<Rep, Period>& duration)
{
    oneSleepDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
}