#include "IPreMessage.h"
#include <algorithm>
#include "LString.h"
#include "IncludeAllPatterens.h"
#include "CharUtilities.h"
#include "IData.h"
#include "BasePattern.h"
namespace Sys
{
    namespace Logging
    {
        IPreMessage::IPreMessage(const UTF8 * patterns, const UTF8* logName) : patteren(createStr(patterns))
        {
            this->Init(patterns, logName);
        }
        template <typename T> void deleteList(std::list<T> l)
        {
            for (auto& i : l)
            {
                delete i.data;
            }
        }
        IPreMessage::~IPreMessage()
        {
            delete[] this->patteren;
            deleteList(nDatas);
            deleteList(unDatas);
        }
        int IPreMessage::getNumOfNecessaryData() const
        {
            return nDatas.size();
        }
        int IPreMessage::getNumOfUnNecessaryData() const
        {
            return unDatas.size();
        }
        void copyDataToArray(const std::list<IndexPattern> datas, IndexData* datasArray)
        {
            int i = 0;
            auto sc = datas.cbegin(), ec = datas.cend();
            while (sc != ec)
            {
                datasArray[i].index = sc->index;
                datasArray[i].data = sc->data->getPattern();
                i++;
                sc++;
            }
        }
        void IPreMessage::getNecessaryData(IndexData* datasArray) const
        {
            copyDataToArray(nDatas, datasArray);
        }
        void IPreMessage::getUnNecessaryData(IndexData* datasArray) const
        {
            copyDataToArray(unDatas, datasArray);
        }
        IndexPattern createIndexPattern(BasePattern* pattern, int index)
        {
            IndexPattern ip;
            ip.data = pattern;
            ip.index = index;
            return ip;
        }
        void addPattern(BasePattern* pattern, std::list<IndexPattern> &datas, int& index)
        {
            datas.push_back(createIndexPattern(pattern, index));
            index++;
        }
        void IPreMessage::Init(const UTF8* pattern, const UTF8* logName)
        {
            const UTF8* p = pattern;
            const UTF8* pre = p;
            const UTF8* l;
            int i = 0;
            while (*p != 0)
            {
                if (*((p)++) == '@')
                {
                    l = this->getDataType(p);
                    if (equalsCaseInsensitive(l, "d", 1))
                    {
                        addPattern(new DateTimePattern(), nDatas, i);
                    }
                    else if (equalsCaseInsensitive(l, "pid", 3))
                    {
                        addPattern(new ProcessDataPattern(), nDatas, i);
                    }
                    else if (equalsCaseInsensitive(l, "msg", 3))
                    {
                        addPattern(new MsgPattern(), unDatas, i);
                    }
                    else if (equalsCaseInsensitive(l, "tid", 3))
                    {
                        addPattern(new ThreadIdPattern(), nDatas, i);
                    }
                    else if (equalsCaseInsensitive(l, "lname", 5))
                    {
                        addPattern(new LoggerNamePattern(String(logName)), unDatas, i);
                    }
                    else if (equalsCaseInsensitive(l, "pname", 5))
                    {
                        addPattern(new ProcessNamePattern(), nDatas, i);
                    }
                    else if (equalsCaseInsensitive(l, "llevel", 6))
                    {
                        addPattern(new LogLevelPattern(), unDatas, i);
                    }
                    else
                    {

                    }
                    delete[] l;
                    pre = p;
                }
            }
        }
        UTF8 * IPreMessage::getDataType(const UTF8 * p)
        {
            if (*p != '[')
            {
                return NULL;
            }
            p++;
            const UTF8 * t = p;
            while (*t != ']'&& t != NULL)
            {
                t++;
            }
            if (t == NULL)
            {
                return NULL;
            }
            int num = t - p;
            UTF8 * ret = new UTF8[num + 1];
            strcpy(ret, p, num);
            ret[num] = 0;
            return ret;
        }
    }
}