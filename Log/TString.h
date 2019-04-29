#ifndef _TSTRING_H_
#define _TSTRING_H_
#include "GlobalDefinitions.h"
namespace Sys
{
    namespace Logging
    {
        template <int CACHE_SIZE = 20> class TString
        {
        public:
            explicit TString();
            explicit TString(unsigned int capacity);
            explicit TString(const UTF8* str);
            explicit TString(UTF8* str, unsigned int len);
            TString(const TString<CACHE_SIZE>&);
            TString(TString<CACHE_SIZE>&&);
            ~TString();
            const UTF8* c_str() const;
            TString<CACHE_SIZE>& append(const UTF8 str);
            TString<CACHE_SIZE>& append(const UTF8* str);
            unsigned int size() const;
            bool empty() const;
            bool operator==(const UTF8*) const;
            bool operator==(const TString<CACHE_SIZE>&) const;
            bool operator<(const UTF8*) const;
            bool operator<(const TString<CACHE_SIZE>&) const;
            TString<CACHE_SIZE>& operator=(const UTF8*);
            TString<CACHE_SIZE>& operator=(const TString<CACHE_SIZE>&);
            TString<CACHE_SIZE>& operator=(TString<CACHE_SIZE>&&);
            TString<CACHE_SIZE>& operator+=(const UTF8*);
            TString<CACHE_SIZE>& operator+=(const TString<CACHE_SIZE>&);
        private:
            void createFromString(const UTF8* str);
            void deleteString();
            UTF8 cacheStr[CACHE_SIZE];
            UTF8* str;
            unsigned int sizeM;
            unsigned int capacity;
        };
    }
}
#include "TString.cpp"
#endif