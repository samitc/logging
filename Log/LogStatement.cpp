#include "LogStatement.h"
#include "IData.h"
#include "PreMessage.h"
#include "CharUtilities.h"
#include "Msg.h"
#include "LogLevel.h"
namespace Sys
{
    namespace Logging
    {
#define MAX_LOG_SIZE    4096
#define MESSAGE_ID      0
#define LEVEL_ID        4
        static char* addSpecialStr(char* str, int msgIndex, const char* msg, int levelIndex, const char* level)
        {
            ReplaceData datas[2];
            ReplaceData msgData;
            msgData.strToPut = msg;
            msgData.pos = msgIndex;
            msgData.charToDelete = 0;
            int count = 2;
            if (msgIndex > levelIndex)
            {
                if (levelIndex != -1)
                {
                    datas[0].strToPut = level;
                    datas[0].pos = levelIndex;
                    datas[0].charToDelete = 0;
                    datas[1] = msgData;
                }
                else
                {
                    datas[0] = msgData;
                    count = 1;
                }
            }
            else
            {
                datas[0] = msgData;
                datas[1].strToPut = level;
                datas[1].pos = levelIndex;
                datas[1].charToDelete = 0;
            }
            return replace(str, datas, count);
        }
        LogStatement::LogStatement(const PreMessage* preMessage, const char* msg, const String& level) :ILogStatement(preMessage), level(level)
        {
            register int l = strlen(msg) + 1;
            this->message = new char[l];
            strcpy(this->message, msg);
        }
        LogStatement::~LogStatement()
        {
            delete[] this->message;
        }
        String LogStatement::getMessage(const IndexData* nData, int nSize) const
        {
            UTF8 finalStr[MAX_LOG_SIZE];
            UTF8* fP = finalStr;
            *fP = 0;
            char* nonPat = ((PreMessage*)(this->getMsg()))->getNonPatteren();
            char* nPat = nonPat;
            int sizeOfUnData = getMsg()->getNumOfUnNecessaryData();
            IndexData* unData = (IndexData*)alloca(sizeOfUnData * sizeof(IndexData));
            getMsg()->getUnNecessaryData(unData);
            int curStrIndex = 0;
            int nIndex = 0;
            int unIndex = 0;
            int countl = 3;
            int messageIndex = -1;
            int levelIndex = -1;
            while (nIndex < nSize || unIndex < sizeOfUnData)
            {
                IData* dat;
                int index;
                if (nIndex == nSize)
                {
                    dat = unData[unIndex].data;
                    index = unData[unIndex].index;
                    unIndex++;
                }
                else if (unIndex == sizeOfUnData)
                {
                    dat = nData[nIndex].data;
                    index = nData[nIndex].index;
                    nIndex++;
                }
                else if (unData[unIndex].index < nData[nIndex].index)
                {
                    dat = unData[unIndex].data;
                    index = unData[unIndex].index;
                    unIndex++;
                }
                else
                {
                    dat = nData[nIndex].data;
                    index = nData[nIndex].index;
                    nIndex++;
                }
                int nonPatIndex = ((PreMessage*)(this->getMsg()))->getIndexInNonPatteren(index);
                if (curStrIndex < nonPatIndex)
                {
                    strcat(fP, nPat, nonPatIndex - curStrIndex);
                    fP += nonPatIndex - curStrIndex;
                    nPat += nonPatIndex - curStrIndex;
                    curStrIndex = nonPatIndex;
                }
                UTF8* t = dat->getData(((PreMessage*)(this->getMsg()))->getPaterenAt(index));
                if (!strcmp(t, Msg::msgStr))
                {
                    strcat(fP, message);
                    fP += strlen(message);
                }
                else if (!strcmp(t, LogLevel::levelStr))
                {
                    strcat(fP, level.c_str());
                    fP += level.size();
                }
                else
                {
                    strcat(fP, t);
                    fP += strlen(t);
                    delete[]t;
                }
                index++;
            }
            for (size_t i = 0; i < sizeOfUnData; i++)
            {
                if (unData[i].toDelete)
                {
                    delete unData[i].data;
                }
            }
            strcat(fP, nonPat + curStrIndex);
            String r(finalStr);
            r.append("\n");
            return r;
        }
    }
}