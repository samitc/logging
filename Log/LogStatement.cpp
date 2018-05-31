#include "LogStatement.h"
#include "IData.h"
#include "PreMessage.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
#define MAX_LOG_SIZE    4096
#define MESSAGE_ID      0
#define LEVEL_ID        4
        char *addSpecialStr(char *str, int msgIndex, const char *msg, int levelIndex, const char *level)
        {
            char *temp;
            if (msgIndex > levelIndex)
            {
                temp = replace(str, msgIndex, msg, 0);
                str = temp;
                if (levelIndex != -1)
                {
                    str = replace(str, levelIndex, level, 0);
                    delete[] temp;
                }
            }
            else
            {
                temp = replace(str, levelIndex, level, 0);
                str = replace(temp, msgIndex, msg, 0);
                delete[] temp;
            }
            return str;
        }
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
            int messageIndex = -1;
            int levelIndex = -1;
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
                ++s;
                int nonPatIndex = ((PreMessage*)(this->msg))->getIndexInNonPatteren(index);
                if (curStrIndex < nonPatIndex)
                {
                    strcat(fP,nPat,nonPatIndex - curStrIndex);
                    fP += nonPatIndex - curStrIndex;
                    nPat += nonPatIndex - curStrIndex;
                    curStrIndex = nonPatIndex;
                }
                if (dat->getNumber() == MESSAGE_ID)
                {
                    messageIndex = fP - finalStr;
                    index++;
                    continue;
                }
                else if (dat->getNumber() == LEVEL_ID)
                {
                    levelIndex = fP - finalStr;
                    index++;
                    continue;
                }
                char * t = dat->getData(((PreMessage*)(this->msg))->getPaterenAt(index));
                strcat(fP,t);
                fP += strlen(t);
                delete []t;
                index++;
            }
            delete [] nonPat;
            char *ret = createStr(finalStr);
            char *temp = addSpecialStr(ret, messageIndex, message, levelIndex, level.c_str());
            delete[]ret;
            ret = temp;
            String r = createString(ret);
            delete[]ret;
            r.append("\n");
            return r;
        }
    }
}
