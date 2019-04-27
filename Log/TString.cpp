#ifndef _TSTRING_CPP_
#define _TSTRING_CPP_
#include "TString.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
#define TEMPLATE_PREFIX template<int CACHE_SIZE>
#define CLASS_DEFENITION TString<CACHE_SIZE>
#define CLASS_NAME TString
#define CLASS_STR_CACHE_SIZE CACHE_SIZE
#include "StringImpl.h"
#undef TEMPLATE_PREFIX
#undef CLASS_DEFENITION
#undef CLASS_NAME
#undef CLASS_STR_CACHE_SIZE
    }
}
#endif