FEATURE library-json.h/Impl
// Work around Android not having std::strtoull implementation.

namespace std
{

unsigned long long strtoull(const char *str, char **endptr, int base)
{
    return ::strtoull(str, endptr, base);
}

} // namespace std
