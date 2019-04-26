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
        struct IndexData;
        class ILogStatement
        {
        public:
            explicit ILogStatement(const IPreMessage *preMessage);
            virtual ~ILogStatement() = default;
            virtual String getMessage(const IndexData* nData, int nSize) const = 0;
        protected:
            const IPreMessage* getMsg() const;
        private:
            const IPreMessage * msg;
        };
    }
}
#endif