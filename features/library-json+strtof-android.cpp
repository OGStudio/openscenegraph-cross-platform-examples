FEATURE library-json.h/Impl
// Work around Android not having std::strtof implementation.

namespace std
{

float strtof(const char *str, char **endptr)
{
    return ::strtof(str, endptr);
}

} // namespace std
