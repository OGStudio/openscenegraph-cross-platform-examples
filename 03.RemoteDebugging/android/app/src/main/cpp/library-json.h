
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_LIBRARY_JSON_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_LIBRARY_JSON_H

// library-json+to_string-android Start
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
// library-json+to_string-android End
// library-json+strtof-android Start
// Work around Android not having std::strtof implementation.

namespace std
{

float strtof(const char *str, char **endptr)
{
    return ::strtof(str, endptr);
}

} // namespace std
// library-json+strtof-android End
// library-json+strtold-android Start
// Work around Android not having std::strtold implementation.

namespace std
{

long double strtold(const char *str, char **endptr)
{
    return ::strtold(str, endptr);
}

} // namespace std
// library-json+strtold-android End
// library-json+strtoull-android Start
// Work around Android not having std::strtoull implementation.

namespace std
{

unsigned long long strtoull(const char *str, char **endptr, int base)
{
    return ::strtoull(str, endptr, base);
}

} // namespace std
// library-json+strtoull-android End
// library-json+strtoll-android Start
// Work around Android not having std::strtoll implementation.

namespace std
{

long long strtoll(const char *str, char **endptr, int base)
{
    return ::strtoll(str, endptr, base);
}

} // namespace std
// library-json+strtoll-android End

#include <nlohmann/json.hpp>

// library-json+Stub Start
// Stub.
// library-json+Stub End

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_LIBRARY_JSON_H

