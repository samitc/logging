#include "StreamParams.h"
#include "FileWriter.h"
#include "ConsoleWriter.h"
#include "NetworkWriter.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
        StreamParam::StreamParam(const StreamParam &copy) :streamType(copy.streamType)
        {
            switch (streamType)
            {
            case StreamType::FILE:
                fileParam = copy.fileParam;
                fileParam.fileName = createStr(fileParam.fileName);
                break;
            case StreamType::NETWORK:
                networkParam = copy.networkParam;
                networkParam.addr = createStr(networkParam.addr);
                break;
            }
        }
        StreamParam & StreamParam::operator=(const StreamParam &eq)
        {
            switch (streamType)
            {
            case StreamType::FILE:
                delete[]fileParam.fileName;
                break;
            case StreamType::NETWORK:
                delete[]networkParam.addr;
                break;
            }
            streamType = eq.streamType;
            switch (streamType)
            {
            case StreamType::FILE:
                fileParam = eq.fileParam;
                fileParam.fileName = createStr(eq.fileParam.fileName);
                break;
            case StreamType::NETWORK:
                networkParam = eq.networkParam;
                networkParam.addr = createStr(eq.networkParam.addr);
                break;
            }
            return *this;
        }
        StreamParam::~StreamParam()
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
        ILoggerWriter * StreamParam::getLoggerWriter() const
        {
            switch (streamType)
            {
            case StreamType::FILE:
                return new FileWriter(fileParam.fileName, fileParam.appendToFile);
                break;
            case StreamType::NETWORK:
                return new NetworkWriter(networkParam.addr, networkParam.port, networkParam.protocol);
                break;
            case StreamType::CONSOLE:
                return new ConsoleWriter();
                break;
            }
            return nullptr;
        }
    }
}