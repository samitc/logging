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
        struct IndexData
        {
            int index;
            IData* data;
        };
        struct IndexPattern
        {
            int index;
            BasePattern* data;
        };
        class IPreMessage
        {
        public:
            IPreMessage(const UTF8 * patterns, const UTF8* logName);
            ~IPreMessage();
            int getNumOfNecessaryData() const;
            int getNumOfUnNecessaryData() const;
            void getNecessaryData(IndexData* datasArray) const;
            void getUnNecessaryData(IndexData* datasArray) const;
        protected:
            UTF8 * patteren;
            std::list<IndexPattern> nDatas;
            std::list<IndexPattern> unDatas;
        private:
            void Init(const UTF8 * patterns, const UTF8* logName);
            UTF8 * getDataType(const UTF8 * p);
        };
    }
}
#endif