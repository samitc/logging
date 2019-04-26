#include "LogData.h"
#include "IData.h"
#include "Configuration.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
        LogData::LogData(Configuration* config, const UTF8* msg, const String& level, const String& name, bool writeImmediately, IndexData* datas, int datasSize, uint64_t logNumber) :
            config(config), datas(datas), sizeOfDatas(datasSize), msg(createStr(msg)), level(level), name(name), shouldWriteInstantly(writeImmediately), logNumber(logNumber)
        {
        }
        LogData::LogData(const UTF8 * msg) : msg(msg), shouldWriteInstantly(false)
        {
        }
        LogData::~LogData()
        {
            delete[] msg;
            for (size_t i = 0; i < sizeOfDatas; i++)
            {
                delete datas[i].data;
            }
            delete[] datas;
        }
        const char * LogData::getMsg() const
        {
            return msg;
        }
        const String & LogData::getLevel() const
        {
            return level;
        }
        const String & LogData::getName() const
        {
            return name;
        }
        bool LogData::getWriteImmediately() const
        {
            return shouldWriteInstantly;
        }
        void LogData::setMsg(UTF8 *m)
        {
            msg = m;
        }
        uint64_t LogData::getLogNumber() const
        {
            return logNumber;
        }
        void LogData::setLogNumber(uint64_t logNumber)
        {
            this->logNumber = logNumber;
        }
        const IndexData* LogData::getDatas() const
        {
            return datas;
        }
        int LogData::getDatasSize() const
        {
            return sizeOfDatas;
        }
        Configuration * LogData::getConfig() const
        {
            return config;
        }
    }
}