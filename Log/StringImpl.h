TEMPLATE_PREFIX CLASS_DEFENITION::CLASS_NAME() :str(nullptr), sizeM(0), capacity(0)
{
}
TEMPLATE_PREFIX CLASS_DEFENITION::CLASS_NAME(unsigned int capacity) : str(nullptr), sizeM(0), capacity(capacity)
{
    if (capacity > CLASS_STR_CACHE_SIZE)
    {
        str = new UTF8[capacity];
    }
}
TEMPLATE_PREFIX CLASS_DEFENITION::CLASS_NAME(const UTF8* str) : CLASS_NAME()
{
    append(str);
}
TEMPLATE_PREFIX CLASS_DEFENITION::CLASS_NAME(UTF8* str, unsigned int len) : str(str), sizeM(len + 1), capacity(len + 1)
{
}
TEMPLATE_PREFIX CLASS_DEFENITION::CLASS_NAME(const CLASS_NAME &copy) : CLASS_NAME(copy.c_str())
{
}
TEMPLATE_PREFIX CLASS_DEFENITION::CLASS_NAME(CLASS_NAME&& str) : str(str.str), sizeM(str.sizeM), capacity(str.capacity)
{
    if (str.str != str.cacheStr)
    {
        str.str = nullptr;
    }
    else
    {
        this->str = cacheStr;
        strcpy(this->str, str.str);
    }
}
TEMPLATE_PREFIX const UTF8 * CLASS_DEFENITION::c_str() const
{
    return str;
}
TEMPLATE_PREFIX void CLASS_DEFENITION::createFromString(const UTF8* str)
{
    sizeM = strlen(str) + 1;
    if (sizeM <= CLASS_STR_CACHE_SIZE)
    {
        this->str = cacheStr;
    }
    else
    {
        if (capacity < sizeM)
        {
            capacity = sizeM;
            this->str = new UTF8[capacity];
        }
    }
    strcpy(this->str, str);
}
TEMPLATE_PREFIX CLASS_DEFENITION& CLASS_DEFENITION::append(const UTF8* str)
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
            if (sizeM > CLASS_STR_CACHE_SIZE && sizeM > capacity)
            {
                capacity = sizeM;
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
TEMPLATE_PREFIX unsigned int CLASS_DEFENITION::size() const
{
    return sizeM - 1;
}
TEMPLATE_PREFIX bool CLASS_DEFENITION::empty() const
{
    return sizeM == 0;
}
TEMPLATE_PREFIX bool CLASS_DEFENITION::operator==(const UTF8 *o) const
{
    return strcmp(c_str(), o) == 0;
}
TEMPLATE_PREFIX bool CLASS_DEFENITION::operator==(const CLASS_NAME &o) const
{
    return *this == o.c_str();
}
TEMPLATE_PREFIX bool CLASS_DEFENITION::operator<(const UTF8 *o) const
{
    return strcmp(c_str(), o) < 0;
}
TEMPLATE_PREFIX bool CLASS_DEFENITION::operator<(const CLASS_NAME &o) const
{
    return *this < o.c_str();
}
TEMPLATE_PREFIX CLASS_DEFENITION & CLASS_DEFENITION::operator=(const UTF8 *o)
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
        capacity = 0;
    }
    return *this;
}
TEMPLATE_PREFIX CLASS_DEFENITION & CLASS_DEFENITION::operator=(const CLASS_NAME &o)
{
    *this = o.c_str();
    return *this;
}
TEMPLATE_PREFIX CLASS_DEFENITION & CLASS_DEFENITION::operator+=(const UTF8 *o)
{
    if (o != nullptr)
    {
        this->append(o);
    }
    return *this;
}
TEMPLATE_PREFIX CLASS_DEFENITION & CLASS_DEFENITION::operator+=(const CLASS_NAME &o)
{
    *this += o.c_str();
    return *this;
}
TEMPLATE_PREFIX void CLASS_DEFENITION::deleteString()
{
    if (str != cacheStr)
    {
        delete[] str;
    }
}
TEMPLATE_PREFIX CLASS_DEFENITION::~CLASS_NAME()
{
    deleteString();
}