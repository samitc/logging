#ifndef _LOGSTATEMENT_H_
#define _LOGSTATEMENT_H_
#include <list>
#include "ILogStatement.h"
#include "LString.h"
namespace Sys
{
    namespace Logging
    {
        class PreMessage;
        class LogStatement :public ILogStatement
        {
        public:
            LogStatement(const PreMessage *preMessage, const char *msg, const String&);
            ~LogStatement() = default;
            virtual String getMessage(const IndexData* nData, int nSize) const;
        private:
            const String &level;
            const char *message;
        };
    }
}
#endif