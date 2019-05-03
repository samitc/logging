#include "LogData.h"
#include <cstring>
#include "IData.h"
#include "Configuration.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
#define MIDDLE_ARRAY_COPY(index) l.datas[(index)],
#define END_ARRAY_COPY(index) l.datas[(index)]
#define MAC(index) MIDDLE_ARRAY_COPY(index)
#define EAC(index) END_ARRAY_COPY(index)
#define ARRAY_COPY MAC(0)MAC(1)MAC(2)MAC(3)MAC(4)MAC(5)MAC(6)MAC(7)MAC(8)MAC(9)MAC(10)MAC(11)MAC(12)MAC(13)MAC(14)MAC(15)MAC(16)MAC(17)MAC(18)EAC(19)
        LogData::LogData(Configuration* config, const UTF8* msg, const UTF8* level, const UTF8* name, bool writeImmediately, uint64_t logNumber) :
            config(config), sizeOfDatas(0), msg(msg), level(level), name(name), shouldWriteInstantly(writeImmediately), logNumber(logNumber)
        {
            sizeOfDatas = config->getSysData()->getNumOfNecessaryData();
            if (sizeOfDatas > LogData::MAX_DATAS)
            {
                throw "Not implement";
            }
            config->getSysData()->getNecessaryData(datas);
        }
        LogData::LogData(const UTF8* msg) : msg(msg), shouldWriteInstantly(false)
        {
        }
        LogData::LogData(LogData&& l) : config(l.config), msg(l.msg), level(l.level), name(l.name), shouldWriteInstantly(l.shouldWriteInstantly), logNumber(l.logNumber), sizeOfDatas(l.sizeOfDatas),
            datas{ARRAY_COPY}
        {
            l.msg = nullptr;
            memset(l.datas, 0, sizeof(l.datas));
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