#ifndef _STRING_H_
#define _STRING_H_
#include "GlobalDefinitions.h"
namespace Sys
{
    namespace Logging
    {
        class String
        {
        public:
            explicit String();
            explicit String(const UTF8* str);
            explicit String(UTF8* str, unsigned int len);
            String(const String&);
            String(String&&);
            ~String();
            const UTF8* c_str() const;
            String& append(const UTF8* str);
            unsigned int size() const;
            bool empty() const;
            bool operator==(const UTF8*) const;
            bool operator==(const String&) const;
            bool operator<(const UTF8*) const;
            bool operator<(const String&) const;
            String& operator=(const UTF8*);
            String& operator=(const String&);
            String& operator+=(const UTF8*);
            String& operator+=(const String&);
        private:
            UTF8 * str;
            unsigned int sizeM;
        };
    }
}
#endif