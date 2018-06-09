FEATURE debug-extlib.h/Impl
// Work around Android not having localeconv() before API 21.
// We target API 14.
#include <clocale>

lconv *localeconv()
{
    static lconv lc;
    return &lc;
}
