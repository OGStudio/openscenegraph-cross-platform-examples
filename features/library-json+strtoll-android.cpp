FEATURE library-json.h/Impl
// Work around Android not having std::strtoll implementation.

namespace std
{

long long strtoll(const char *str, char **endptr, int base)
{
    return ::strtoll(str, endptr, base);
}

} // namespace std
