#ifndef _PREMESSAGE_H_
#define _PREMESSAGE_H_
#include <vector>
#include "IPreMessage.h"
namespace Sys
{
    namespace Logging
    {
        class PreMessage :public IPreMessage
        {
        public:
            PreMessage(const UTF8 * patteren, const UTF8* logName);
            ~PreMessage();
            const UTF8* const getLogName();
            UTF8* getNonPatteren();
            UTF8 * getPaterenAt(int index) const;
            int getIndexInNonPatteren(int index) const;
        protected:
            void Init(const UTF8 * patteren);
            UTF8 **specificPatterens;
            UTF8* nonPatteren;
            UTF8* logName;
            int *spesificPatIndex;
        private:
            UTF8 * getSpecificPatterens(const UTF8 * p, int * size);
        };
    }
}
#endif
