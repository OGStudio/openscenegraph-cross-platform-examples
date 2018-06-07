FEATURE library-json.h/Impl
// Work around Android not having std::to_string implementation.
#include <string>
#include <sstream>

namespace std
{

template <typename T>
inline std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

} // namespace std
