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
            explicit String(unsigned int capacity);
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
            void createFromString(const UTF8* str);
            void deleteString();
            static const int CACHE_STR_SIZE = 20;
            UTF8 cacheStr[CACHE_STR_SIZE];
            UTF8 * str;
            unsigned int sizeM;
            unsigned int capacity;
        };
    }
}
#endif