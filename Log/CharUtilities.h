#ifndef _CHARUTILITIES_H_
#define _CHARUTILITIES_H_
#include <ostream>
#include "GlobalDefinitions.h"
namespace Sys
{
    namespace Logging
    {
        struct ReplaceData
        {
            int pos;
            int charToDelete;
            char *strToPut;
        };
        class String;
        using byte = unsigned char;
        using Stream = std::basic_ostream<char>;
        using UTF8 = char;
        int strlen(const UTF8*);
        int strlen(const String&);
        void strcpy(UTF8 *, const UTF8*);
        void strcpy(UTF8 *, const UTF8*, int);
        void strcat(UTF8 *, const UTF8*);
        void strcat(UTF8 *, const UTF8*, int);
        char* replace(const UTF8*, int, const UTF8*, int);
        char* replace(const UTF8*, ReplaceData*, int);
        int find(const UTF8*, const UTF8*);
        int strcmp(const UTF8*, const UTF8*);
        int strToInt(const UTF8*);
        String createString(const UTF8*);
        void stringToLower(char * UTF8);
        void stringToUpper(char *UTF8);
        bool equels(const UTF8 * strA, const UTF8 * strB, int count);
        char* fromUtf8(const UTF8*);
        UTF8* toUtf8(const char*);
        UTF8* createStr(const UTF8*);
        void itca(int, UTF8*, int);
    }
}
#include "String.h"
#endif
