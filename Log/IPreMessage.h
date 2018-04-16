#ifndef _IPREMESSAGE_H_
#define _IPREMESSAGE_H_
#include <list>
#include "GlobalDefinitions.h"
#include <memory>
namespace Sys
{
    namespace Logging
    {
        class IData;
        class BasePattern;
        class IPreMessage
        {
        public:
            IPreMessage(const UTF8 * patterns, const UTF8* logName);
            ~IPreMessage();
            std::list<IData*>* getDatas() const;
            std::list<IData*> getNecessaryData() const;
        protected:
            UTF8 * patteren;
            std::list<BasePattern*> datas;
            std::list<BasePattern*> nDatas;
            std::list<BasePattern*> unDatas;
        private:
            void Init(const UTF8 * patterns, const UTF8* logName);
            UTF8 * getDataType(const UTF8 * p);
        };
    }
}
#endif