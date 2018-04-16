#include "IPreMessage.h"
#include <string>
#include <algorithm>
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
        IPreMessage::~IPreMessage()
        {
            delete[] this->patteren;
            for (auto &dat : datas)
            {
                delete dat;
            }
        }
        void IPreMessage::Init(const UTF8 * pattern, const UTF8* logName)
        {
            UTF8 *patterns = createStr(pattern);
            stringToLower(patterns);
            UTF8 * p = patterns;
            UTF8 * pre = p;
            UTF8 * l;
            BasePattern *add;
            while (*p != 0)
            {
                if (*((p)++) == '@')
                {
                    l = this->getDataType(p);
                    if (equels(l, "d", 1))
                    {
                        add = new DateTimePattern();
                        datas.push_back(add);
                        nDatas.push_back(add);
                    }
                    else if (equels(l, "pid", 3))
                    {
                        add = new ProcessDataPattern();
                        datas.push_back(add);
                        nDatas.push_back(add);
                    }
                    else if (equels(l, "msg", 3))
                    {
                        add = new MsgPattern();
                        datas.push_back(add);
                        unDatas.push_back(add);
                    }
                    else if (equels(l, "tid", 3))
                    {
                        add = new ThreadIdPattern();
                        datas.push_back(add);
                        nDatas.push_back(add);
                    }
                    else if (equels(l, "lname", 5))
                    {
                        add = new LoggerNamePattern(String(logName));
                        datas.push_back(add);
                        unDatas.push_back(add);
                    }
                    else if (equels(l, "pname", 5))
                    {
                        add = new ProcessNamePattern();
                        datas.push_back(add);
                        nDatas.push_back(add);
                    }
                    else if (equels(l, "llevel", 6))
                    {
                        add = new LogLevelPattern();
                        datas.push_back(add);
                        unDatas.push_back(add);
                    }
                    else
                    {

                    }
                    delete[] l;
                    pre = p;
                }
            }
            for (const auto & pat : datas)
            {
                pat->setPattern(&datas);
                pat->prepeareLogger();
            }
            delete[] patterns;
        }
        std::list<IData*>* IPreMessage::getDatas() const
        {
            std::list<IData*> *datas = new std::list<IData*>();
            auto sc = this->datas.cbegin(), ec = this->datas.cend();
            while (sc != ec)
            {
                datas->push_back((*sc)->getPattern());
                sc++;
            }
            return datas;
        }
        std::list<IData*> IPreMessage::getNecessaryData() const
        {
            std::list<IData*> datas;
            auto sc = this->nDatas.cbegin(), ec = this->nDatas.cend();
            while (sc != ec)
            {
                datas.push_back((*sc)->getPattern());
                sc++;
            }
            return datas;
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