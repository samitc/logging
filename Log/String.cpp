#include "String.h"
namespace Sys
{
    namespace Logging
    {
        String::String() :str(nullptr), sizeM(0)
        {
        }
        String::String(const UTF8 * str) : String()
        {
            if (str != nullptr)
            {
                sizeM = strlen(str) + 1;
                this->str = new UTF8[sizeM];
                strcpy(this->str, str);
            }
        }
        String::String(UTF8 * str, unsigned int len) :str(str), sizeM(len + 1)
        {
        }
        String::String(const String &copy) : String(copy.c_str())
        {
        }
        String::String(String &&str) : str(str.str), sizeM(str.sizeM)
        {
            str.str = nullptr;
        }
        const UTF8 * String::c_str() const
        {
            return str;
        }
        String & String::append(const UTF8 * str)
        {
            if (empty())
            {
                sizeM = strlen(str) + 1;
                this->str = new char[sizeM];
                strcpy(this->str, str);
            }
            else
            {
                sizeM = strlen(str) + size() + 1;
                UTF8 *newStr = new UTF8[sizeM];
                strcpy(newStr, this->str);
                strcat(newStr, str);
                delete[]this->str;
                this->str = newStr;
            }
            return *this;
        }
        unsigned int String::size() const
        {
            return sizeM;
        }
        bool String::empty() const
        {
            return size() == 0;
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
                sizeM = strlen(o) + 1;
                this->str = new UTF8[sizeM];
                strcpy(this->str, o);
            }
            else
            {
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
        String::~String()
        {
            delete[] str;
        }
    }
}