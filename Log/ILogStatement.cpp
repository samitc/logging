#include "ILogStatement.h"
#include "IPreMessage.h"
#include "IData.h"
namespace Sys
{
    namespace Logging
    {
        ILogStatement::ILogStatement(const IPreMessage *preMessage)
        {
            this->msg = preMessage;
            this->datas = preMessage->getDatas();
        }
        ILogStatement::~ILogStatement()
        {
            auto s = this->datas->begin(), e = this->datas->end();
            while (s != e)
            {
                delete(*s);
                s++;
            }
            delete this->datas;
        }
    }
}