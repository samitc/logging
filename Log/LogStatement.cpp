#include "LogStatement.h"
#include "IData.h"
#include "PreMessage.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
#define MAX_LOG_SIZE    4096
        LogStatement::LogStatement(const PreMessage *preMessage, const char* msg, const String& level) :ILogStatement(preMessage), level(level)
        {
            register int l = strlen(msg) + 1;
            this->message = new char[l];
            strcpy(this->message, msg);
        }
        LogStatement::~LogStatement()
        {
            delete[] this->message;
        }
        String LogStatement::getMessage(const std::list<IData*>& datas) const
        {
            UTF8 finalStr[MAX_LOG_SIZE];
            UTF8* fP = finalStr;
            *fP = 0;
            char* nonPat = createStr(((PreMessage*)(this->msg))->getNonPatteren());
            char* nPat = nonPat;
            auto s = this->datas->begin(), e = this->datas->end();
            auto ds = datas.cbegin(), de = datas.cend();
            int curStrIndex = 0;
            int index = 0;
            int countl = 3;
            while (s != e)
            {
                IData* dat;
                if ((*s)->getNumber() == (*ds)->getNumber())
                {
                    dat = *ds;
                    ++ds;
                }
                else
                {
                    dat = *s;
                }
                char * t = dat->getData(((PreMessage*)(this->msg))->getPaterenAt(index));
                int nonPatIndex = ((PreMessage*)(this->msg))->getIndexInNonPatteren(index);
                if (curStrIndex < nonPatIndex)
                {
                    strcat(fP,nPat,nonPatIndex - curStrIndex);
                    fP += nonPatIndex - curStrIndex;
                    nPat += nonPatIndex - curStrIndex;
                    curStrIndex = nonPatIndex;
                }
                strcat(fP,t);
                fP += strlen(t);
                delete []t;
                ++s;
                index++;
            }
            delete [] nonPat;
            char *ret = createStr(finalStr);
            char* temp = replace(ret, find(ret, "~!@"), message, 3);
            delete[]ret;
            ret = temp;
            auto indexName = find(ret, "@`~");
            if (indexName != -1)
            {
                temp = replace(ret, indexName, level.c_str(), 3);
                delete[]ret;
                ret = temp;
            }
            String r = createString(ret);
            delete[]ret;
            r.append("\n");
            return r;
        }
    }
}
