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
        LogStatement::LogStatement(const PreMessage* preMessage, const char* msg, const String& level) :ILogStatement(preMessage), level(level),message(msg)
        {
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
                const UTF8* t = dat->getData(((PreMessage*)(this->getMsg()))->getPaterenAt(index));
                if (!strcmp(t, Msg::msgStr))
                {
                    t = message;
                }
                else if (!strcmp(t, LogLevel::levelStr))
                {
                    t = level.c_str();
                }
                strcat(fP, t);
                fP += strlen(t);
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
            fP += strlen(fP);
            *fP = '\n';
            *(++fP) = 0;
            return String(finalStr);
        }
    }
}