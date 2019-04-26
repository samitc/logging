#include "LString.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
        String::String() :str(nullptr), sizeM(0)
        {
        }
        String::String(const UTF8* str) : String()
        {
            append(str);
        }
        String::String(UTF8 * str, unsigned int len) :str(str), sizeM(len + 1)
        {
        }
        String::String(const String &copy) : String(copy.c_str())
        {
        }
        String::String(String&& str) : str(str.str), sizeM(str.sizeM)
        {
            if (str.sizeM > CACHE_STR_SIZE)
            {
                str.str = nullptr;
            }
            else
            {
                this->str = cacheStr;
                strcpy(this->str, str.str);
            }
        }
        const UTF8 * String::c_str() const
        {
            return str;
        }
        void String::createFromString(const UTF8* str)
        {
            sizeM = strlen(str) + 1;
            if (sizeM <= CACHE_STR_SIZE)
            {
                this->str = cacheStr;
            }
            else
            {
                this->str = new UTF8[sizeM];
            }
            strcpy(this->str, str);
        }
        String& String::append(const UTF8* str)
        {
            if (str != nullptr)
            {
                if (empty())
                {
                    createFromString(str);
                }
                else
                {
                    sizeM = strlen(str) + size() + 1;
                    if (sizeM > CACHE_STR_SIZE)
                    {
                        UTF8* newStr = new UTF8[sizeM];
                        strcpy(newStr, this->str);
                        deleteString();
                        this->str = newStr;
                    }
                    strcat(this->str, str);
                }
            }
            return *this;
        }
        unsigned int String::size() const
        {
            return sizeM - 1;
        }
        bool String::empty() const
        {
            return sizeM == 0;
        }
        bool String::operator==(const UTF8 *o) const
        {
            return strcmp(c_str(), o) == 0;
        }
        bool String::operator==(const String &o) const
        {
            return *this == o.c_str();
        }
        bool String::operator<(const UTF8 *o) const
        {
            return strcmp(c_str(), o) < 0;
        }
        bool String::operator<(const String &o) const
        {
            return *this < o.c_str();
        }
        String & String::operator=(const UTF8 *o)
        {
            if (o != nullptr)
            {
                deleteString();
                createFromString(o);
            }
            else
            {
                deleteString();
                str = nullptr;
                sizeM = 0;
            }
            return *this;
        }
        String & String::operator=(const String &o)
        {
            *this = o.c_str();
            return *this;
        }
        String & String::operator+=(const UTF8 *o)
        {
            if (o != nullptr)
            {
                this->append(o);
            }
            return *this;
        }
        String & String::operator+=(const String &o)
        {
            *this += o.c_str();
            return *this;
        }
        void String::deleteString()
        {
            if (str != cacheStr)
            {
                delete[] str;
            }
        }
        String::~String()
        {
            deleteString();
        }
    }
}
