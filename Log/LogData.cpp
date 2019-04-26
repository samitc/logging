#include "LogData.h"
#include "IData.h"
#include "Configuration.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
        LogData::LogData(Configuration* config, const UTF8* msg, const String& level, const String& name, bool writeImmediately, uint64_t logNumber) :
            config(config), sizeOfDatas(0), msg(createStr(msg)), level(level), name(name), shouldWriteInstantly(writeImmediately), logNumber(logNumber)
        {
            sizeOfDatas = config->getSysData()->getNumOfNecessaryData();
            if (sizeOfDatas>LogData::MAX_DATAS)
            {
                throw "Not implement";
            }
            config->getSysData()->getNecessaryData(datas);
        }
        LogData::LogData(const UTF8 * msg) : msg(msg), shouldWriteInstantly(false)
        {
        }
        LogData::~LogData()
        {
            delete[] msg;
            for (size_t i = 0; i < sizeOfDatas; i++)
            {
                if (datas[i].toDelete)
                {
                    delete datas[i].data;
                }
            }
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