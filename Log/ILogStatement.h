#ifndef _ILOGSTATEMENT_H_
#define _ILOGSTATEMENT_H_
#include <list>
#include "GlobalDefinitions.h"
#include "LString.h"
namespace Sys
{
    namespace Logging
    {
        class IPreMessage;
        class IData;
        class ILogStatement
        {
        public:
            explicit ILogStatement(const IPreMessage *preMessage);
            virtual ~ILogStatement();
            virtual String getMessage(const std::list<IData*>&) const = 0;
        protected:
            const IPreMessage * msg;
            std::list<IData*> *datas;
        };
    }
}
#endif