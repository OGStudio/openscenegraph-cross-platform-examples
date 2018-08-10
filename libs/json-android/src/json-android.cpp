
// Work around Android not having localeconv() before API 21.
// We target API 14.
#include <clocale>

lconv *localeconv()
{
    static lconv lc;
    return &lc;
}

// Work around Android not having several STL functions in std.

#include <cstdlib>
#include <string>
#include <sstream>

namespace std
{
using ::strtof;
using ::strtold;
using ::strtoll;
using ::strtoull;
using ::snprintf;

template <typename T>
inline std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

inline int stoi(const std::string &s, size_t *idx = 0, int base = 10)
{
    char *endptr = 0;
    int result = strtol(s.c_str(), &endptr, base);
    if (idx)
	{
        *idx = endptr - s.c_str();
    }
    return result;
}

} // namespace std

