FEATURE library-json.h/Impl
// Work around Android not having localeconv() prior SDK 21.
#include <clocale>

lconv *localeconv()
{
    static lconv lc;
    return &lc;
}

