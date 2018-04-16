#include "LogStatement.h"
#include "IData.h"
#include "PreMessage.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
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
            char* ret = createStr(((PreMessage*)(this->msg))->getNonPatteren());
            std::list<IData *>::iterator s = this->datas->begin(), e = this->datas->end();
            auto ds = datas.cbegin(), de = datas.cend();
            int index = 0;
            char sh[6];
            sh[0] = '~';
            sh[1] = '0';
            sh[2] = '~';
            sh[3] = 0;
            sh[4] = 0;
            sh[5] = 0;
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
                char *temp = ret;
                if (t != nullptr)
                {
                    temp = replace(ret, find(ret, sh), t, countl);
                    delete[] ret;
                    delete[] t;
                }
                ret = temp;
                ++s;
                index++;
                if (index == 10)
                {
                    sh[3] = '~';
                    sh[1] = '0';
                    sh[2] = '1';
                    sh[4] = 0;
                }
                else if (index == 100)
                {
                    sh[5] = 0;
                    sh[4] = '~';
                    sh[2] = '0';
                    sh[3] = '1';
                    sh[1] = '0';
                }
                else if (index > 10)
                {
                    sh[1] = index % 10 + '0';
                    sh[2] = index / 10 + '0';
                }
                else if (index > 100)
                {
                    sh[1] = index % 100 + '0';
                    sh[2] = (index / 10) % 10 + '0';
                    sh[3] = index / 100 + '0';
                }
                else
                {
                    sh[1] = index % 10 + '0';
                }
            }
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