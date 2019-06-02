#include "NetworkWriterMock.h"
#include <thread>
NetworkWriterMock::NetworkWriterMock(const char* addr, unsigned short port, Protocol protocol) :NetworkWriter(addr, port, protocol)
{
}
NetworkWriterMock::~NetworkWriterMock()
{
}
void NetworkWriterMock::write(const char* text) const
{
    callbackBeforeWrite(text);
    std::this_thread::sleep_for(oneSleepDuration);
    oneSleepDuration = std::chrono::nanoseconds(0);
    NetworkWriter::write(text);
}
void NetworkWriterMock::setCallbackBeforeWrite(const std::function<void(const char*)>& f)
{
    callbackBeforeWrite = f;
}