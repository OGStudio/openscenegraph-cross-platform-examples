
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_FORMAT_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_FORMAT_H

// printfString Start
#include <cstdarg>

// printfString End

namespace osgcpe
{
namespace format
{

// printfString Start
//! Construct a string using printf-like syntax.
std::string printfString(const char *fmt, ...)
{
    const int PRINTF_STRING_MAX_STRLEN = 1024;
    va_list args;
    char msg[PRINTF_STRING_MAX_STRLEN];
    va_start(args, fmt);
    vsnprintf(msg, PRINTF_STRING_MAX_STRLEN, fmt, args);
    va_end(args);
    return msg;
}
// printfString End
// splitString Start
//! Split a string into a list of strings using a single character.
std::vector<std::string> splitString(const std::string &s, const char *c)
{
    size_t pos = 0;
    bool proceed = true;
    bool hasChar = false;
    std::vector<std::string> result;
    while (proceed)
    {
        auto id = s.find(c, pos);
        if (id != std::string::npos)
        {
            result.push_back(s.substr(pos, id - pos));
            pos = id + 1;
            hasChar = true;
        }
        else
        {
            result.push_back(s.substr(pos, s.length()));
            proceed = false;
            // If delimiting char has not been found,
            // the result should only contain original string.
        }
    }
    return result;
}
// splitString End


} // namespace format
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_FORMAT_H

