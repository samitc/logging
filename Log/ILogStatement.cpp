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
        }
        const IPreMessage* ILogStatement::getMsg() const
        {
            return msg;
        }
    }
}