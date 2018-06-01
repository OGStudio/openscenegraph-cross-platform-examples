FEATURE library-json.h/Impl
// Work around Android not having std::strtold implementation.

namespace std
{

long double strtold(const char *str, char **endptr)
{
    return ::strtold(str, endptr);
}

} // namespace std
