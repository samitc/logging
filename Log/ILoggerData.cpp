#include "ILoggerData.h"
#include "FileWriter.h"
#include "ConsoleWriter.h"
#include "NetworkWriter.h"
namespace Sys
{
    namespace Logging
    {
        ILoggerData::~ILoggerData() {}
        ILoggerData::StreamParam::StreamParam(const StreamParam &copy) :streamType(copy.streamType)
        {
            switch (streamType)
            {
            case Sys::Logging::ILoggerData::StreamType::FILE:
                fileParam = copy.fileParam;
                fileParam.fileName = createStr(fileParam.fileName);
                break;
            case Sys::Logging::ILoggerData::StreamType::NETWORK:
                networkParam = copy.networkParam;
                networkParam.addr = createStr(networkParam.addr);
                break;
            }
        }
        ILoggerData::StreamParam & ILoggerData::StreamParam::operator=(const StreamParam &eq)
        {
            switch (streamType)
            {
            case Sys::Logging::ILoggerData::StreamType::FILE:
                delete[]fileParam.fileName;
                break;
            case Sys::Logging::ILoggerData::StreamType::NETWORK:
                delete[]networkParam.addr;
                break;
            }
            streamType = eq.streamType;
            switch (streamType)
            {
            case Sys::Logging::ILoggerData::StreamType::FILE:
                fileParam = eq.fileParam;
                fileParam.fileName = createStr(eq.fileParam.fileName);
                break;
            case Sys::Logging::ILoggerData::StreamType::NETWORK:
                networkParam = eq.networkParam;
                networkParam.addr = createStr(eq.networkParam.addr);
                break;
            }
            return *this;
        }
        ILoggerData::StreamParam::~StreamParam()
        {
            if (streamType == StreamType::NETWORK)
            {
                delete[] networkParam.addr;
            }
            else if (streamType == StreamType::FILE)
            {
                delete[] fileParam.fileName;
            }
        }
        ILoggerWriter * ILoggerData::StreamParam::getLoggerWriter() const
        {
            switch (streamType)
            {
            case Sys::Logging::ILoggerData::StreamType::FILE:
                return new FileWriter(fileParam.fileName, fileParam.appendToFile);
                break;
            case Sys::Logging::ILoggerData::StreamType::NETWORK:
                return new NetworkWriter(networkParam.addr, networkParam.port, networkParam.protocol);
                break;
            case Sys::Logging::ILoggerData::StreamType::CONSOLE:
                return new ConsoleWriter();
                break;
            }
            return nullptr;
        }
    }
}