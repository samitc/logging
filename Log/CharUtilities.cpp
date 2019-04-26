#include "CharUtilities.h"
#include <string.h>
#include "LString.h"
namespace Sys
{
    namespace Logging
    {
        char toLower(char p)
        {
            return p | 0x20;
        }
        char toUpper(char p)
        {
            return p & 0xDF;
        }
        void stringToLower(char *p)
        {
            while (*p != 0)
            {
                *p = toLower(*p);
                p++;
            }
        }
        void stringToUpper(char *p)
        {
            while (*p != 0)
            {
                *p = toUpper(*p);
                p++;
            }
        }
        bool equalsCaseInsensitive(const UTF8* strA, const UTF8* strB, int count)
        {
            while (count > 0 && (*strA) != 0 && (*strB) != 0)
            {
                if (toLower(*strA) != toLower(*strB))
                {
                    return false;
                }
                strA++;
                strB++;
                count--;
            }
            return true;
        }
        int strlen(const UTF8 *str)
        {
            return ::strlen(str);
        }
        int strlen(const String &str)
        {
            return str.size();
        }
        void strcpy(UTF8 *dst, const UTF8 *src)
        {
            ::strcpy(dst, src);
        }
        void strcpy(UTF8 *dst, const UTF8 *src, int c)
        {
            ::strncpy(dst, src, c);
        }
        void strcat(UTF8 *dst, const UTF8 *src)
        {
            ::strcat(dst, src);
        }
        void strcat(UTF8* dst, const UTF8 *src, int n)
        {
            ::strncat(dst, src, n);
        }
        char * replace(const UTF8 *str, int pos, const UTF8 *strToPut, int charToDelete)
        {
            register int lP = strlen(strToPut);
            register int l = strlen(str) + lP - charToDelete + 1;
            char* ret = new char[l];
            char* p = ret;
            const char* s = str;
            const char* sP = strToPut;
            while (pos-- != 0)
            {
                *(p++) = *(s++);
            }
            while (lP-- != 0)
            {
                *(p++) = *(sP++);
            }
            s += charToDelete;
            while (*s != NULL)
            {
                *(p++) = *(s++);
            }
            *p = NULL;
            return ret;
        }
        char* replace(const UTF8* str, ReplaceData* datas, int numOfDatas)
        {
            int totalLen = strlen(str) + 1;
            for (int i = 0; i < numOfDatas; i++)
            {
                totalLen += strlen(datas[i].strToPut) - datas[i].charToDelete;
            }
            char *ret = new char[totalLen];
            char *p = ret;
            const UTF8 *pStr = str;
            int deletedChar = 0;
            for (int i = 0; i < numOfDatas; i++)
            {
                const UTF8 *pNextStr = str + datas[i].pos;
                while (pStr < pNextStr)
                {
                    *(p++) = *(pStr++);
                }
                const UTF8 *pSTP = datas[i].strToPut;
                while (*pSTP != NULL)
                {
                    *(p++) = *(pSTP++);
                }
                pStr += datas[i].charToDelete;
                deletedChar += datas[i].charToDelete;
            }
            strcpy(p,pStr);
            return ret;
        }
        int find(const UTF8 *str, const UTF8 *strToFind)
        {
            const char* s = str;
            while (*s != NULL)
            {
                if (*(s++) == *strToFind)
                {
                    const char* ss = s;
                    const char* f = strToFind + 1;
                    while (*f != NULL && *ss != NULL && *(ss++) == *(f++));
                    if (*f == NULL)
                    {
                        return s - str - 1;
                    }
                }
            }
            return -1;
        }
        int strcmp(const UTF8 *s1, const UTF8 *s2)
        {
            return ::strcmp(s1, s2);
        }
        int strToInt(const UTF8 *str)
        {
            return ::atoi(str);
        }
        String createString(const UTF8 *str)
        {
            return String(str);
        }
        char * fromUtf8(const UTF8 *str)
        {
            return createStr(str);
        }
        UTF8 * toUtf8(const char *str)
        {
            return createStr(str);
        }
        UTF8 * createStr(const UTF8 *str)
        {
            register int l = strlen(str) + 1;
            char* ret = new char[l];
            strcpy(ret, str);
            return ret;
        }
        void itca(int number, UTF8 *str, int maxNumber)
        {
            int index = 0;
            if (number > 0)
            {
                char* characters = (char*)alloca(maxNumber);
                while (number > 0 && index < maxNumber)
                {
                    characters[index] = number % 10 + '0';
                    number /= 10;
                    ++index;
                }
                for (int i = 0; i < index; ++i)
                {
                    str[i] = characters[index - i - 1];
                }
            }
            else
            {
                str[index++] = '0';
            }
            str[index] = '\0';
        }
    }
}
