#ifndef _LOGSTATEMENT_H_
#define _LOGSTATEMENT_H_
#include <list>
#include "ILogStatement.h"
namespace Sys
{
    namespace Logging
    {
        class PreMessage;
        class LogStatement :public ILogStatement
        {
        public:
            LogStatement(const PreMessage *preMessage, const char *msg, const String&);
            virtual ~LogStatement();
            virtual String getMessage(const std::list<IData*>&) const;
        private:
            String level;
            char *message;
        };
    }
}
#endif