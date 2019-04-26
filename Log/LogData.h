#ifndef _LOGDATA_H_
#define _LOGDATA_H_
#include <list>
#include <stdint.h>
#include "GlobalDefinitions.h"
#include "LString.h"
#include "IPreMessage.h"
namespace Sys
{
    namespace Logging
    {
        class IData;
        class Configuration;

        class LogData
        {
        public:
            LogData(Configuration* config, const UTF8* msg, const String& level, const String& name, bool writeImmediately, uint64_t logNumber);
            explicit LogData(const UTF8* msg);
            ~LogData();
            const char* getMsg() const;
            const String& getLevel() const;
            const String& getName() const;
            bool getWriteImmediately() const;
            void setMsg(UTF8*);
            uint64_t getLogNumber() const;
            void setLogNumber(uint64_t logNumber);
            const IndexData* getDatas() const;
            int getDatasSize() const;
            Configuration* getConfig() const;
        private:
            static const int MAX_DATAS = 20;
            uint64_t logNumber;
            Configuration* config;
            IndexData datas[LogData::MAX_DATAS];
            int sizeOfDatas;
            const UTF8* msg;
            String level;
            String name;
            bool shouldWriteInstantly;
        };
    }
}
#endif