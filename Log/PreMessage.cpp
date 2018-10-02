#include "PreMessage.h"
#include "IData.h"
#include "GlobalDefinitions.h"
#include "LString.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
        PreMessage::PreMessage(const UTF8 * patteren, const UTF8* logName) :IPreMessage(patteren, logName)
        {
            this->specificPatterens = new UTF8*[IPreMessage::datas.size()];
            this->spesificPatIndex = new int[IPreMessage::datas.size()];
            this->Init(patteren);
            this->logName = createStr(logName);
        }
        PreMessage::~PreMessage()
        {
            for (int i = 0, count = IPreMessage::datas.size(); i < count; i++)
            {
                if (this->specificPatterens[i] != nullptr)
                {
                    delete[] this->specificPatterens[i];
                }
            }
            delete[] this->specificPatterens;
            delete[] this->spesificPatIndex;
            if (nonPatteren != "")
            {
                delete[] nonPatteren;
            }
            delete[]logName;
        }
        const UTF8 * const PreMessage::getLogName()
        {
            return this->logName;
        }
        void PreMessage::Init(const UTF8 * patteren)
        {
            String nonPatteren;
            const UTF8 * p = patteren;
            register int index = 0;
            const int SIZE = 25;
            UTF8 buf[SIZE];
            buf[SIZE - 1] = 0;
            int index1 = 0;
            int size;
            char *indexTmp = (char*)alloca(101);
            while (*p != 0)
            {
                if (*p == '@')
                {
                    this->specificPatterens[index] = this->getSpecificPatterens(p, &size);
                    if (index1 != 0)
                    {
                        buf[index1] = 0;
                        nonPatteren.append(buf);
                        index1 = 0;
                    }
                    spesificPatIndex[index] = nonPatteren.size();
                    p += size;
                    index++;
                }
                else
                {
                    buf[index1] = *p;
                    index1++;
                    if (index1 == SIZE - 1)
                    {
                        buf[SIZE - 1] = 0;
                        nonPatteren.append(buf);
                        index1 = 0;
                    }
                    p++;
                }
            }
            if (index1 != 0)
            {
                buf[index1] = 0;
                nonPatteren.append(buf);
            }
            if (nonPatteren.c_str() == nullptr)
            {
                this->nonPatteren = "";
            }
            else
            {
                this->nonPatteren = createStr(nonPatteren.c_str());
            }
        }
        UTF8 * PreMessage::getPaterenAt(int index) const
        {
            return this->specificPatterens[index];
        }
        int PreMessage::getIndexInNonPatteren(int index) const
        {
            return spesificPatIndex[index];
        }
        UTF8 * PreMessage::getSpecificPatterens(const UTF8 * p, int *size)
        {
            const UTF8 * start = p;
            while (*p != 0 && *p != ']')
            {
                p++;
            }
            if (*p == 0)
            {
                return nullptr;
            }
            *size = p - start + 1;
            ++p;
            const UTF8 * pre = p;
            if (*(p) == '{')
            {
                p++;
                while (*p != '}'&&p != NULL)
                {
                    p++;
                }
                if (*p == 0)
                {
                    throw new int(0);
                }
                *size = p - start + 1;
            }
            register int len = p - pre;
            if (len == 0)
            {
                return nullptr;
            }
            UTF8 * ret = new UTF8[len];
            strcpy(ret, pre + 1, len);
            ret[len - 1] = 0;
            return ret;
        }
        UTF8* PreMessage::getNonPatteren()
        {
            return this->nonPatteren;
        }
    }
}
