#ifndef _LOGDATA_H_
#define _LOGDATA_H_
#include "GlobalDefinitions.h"
#include <list>
namespace Sys
{
    namespace Logging
    {
        class IData;
        class Configuration;
        class LogData
        {
        public:
            LogData(Configuration *config, const UTF8* msg, const String &level, const String &name, bool writeImmediately, std::list<IData*>&, uint64_t logNumber);
            explicit LogData(const UTF8* msg);
            ~LogData();
            const char * getMsg() const;
            const String &getLevel() const;
            const String &getName() const;
            bool getWriteImmediately() const;
            void setMsg(UTF8*);
            uint64_t getLogNumber() const;
            void setLogNumber(uint64_t logNumber);
            const std::list<IData*>& getDatas() const;
            Configuration* getConfig() const;
        private:
            uint64_t logNumber;
            Configuration* config;
            std::list<IData*> datas;
            const UTF8* msg;
            String level;
            String name;
            bool shouldWriteInstantly;
        };
    }
}
#endif