#include "LString.h"
#include "CharUtilities.h"
namespace Sys
{
    namespace Logging
    {
#define TEMPLATE_PREFIX
#define CLASS_DEFENITION String
#define CLASS_NAME String
#define CLASS_STR_CACHE_SIZE CACHE_STR_SIZE
#include "StringImpl.h"
#undef TEMPLATE_PREFIX
#undef CLASS_DEFENITION
#undef CLASS_NAME
#undef CLASS_STR_CACHE_SIZE
    }
}
