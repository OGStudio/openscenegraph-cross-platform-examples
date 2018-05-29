
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_H

// debug+pageToJSON Start
#include "DebugPage.h"

// debug+pageToJSON End

namespace osgcpe
{
namespace debug
{

// debug+pageToJSON Start
std::string pageToJSON(DebugPage page)
{
    // Format items.
    std::string format;
    format += "{";
    format += "\"title\":\"%s\",";
    format += "\"value\":\"%s\",";
    format += "\"isWritable\":%d"; // Note the absent comma.
    format += "}";
    std::string itemsJSON = "";
    for (auto item : page.items)
    {
        // Add comma if we're adding second and later items.
        if (!itemsJSON.empty())
        {
            itemsJSON += ",";
        }
        // Add item.
        auto title = item.title;
        auto value = item.getter();
        bool isWritable = (item.setter != nullptr);
        itemsJSON +=
            log::printfString(
                format.c_str(),
                title.c_str(),
                value.c_str(),
                isWritable
            );
    }

    // Format page.
    std::string json;
    json += "{";

    json += "\"title\":\"";
    json += page.title;
    json += "\",";

    json += "\"items\":[";
    json += itemsJSON;
    json += "]"; // Note the absent comma.

    json += "}";
    return json;
}

// debug+pageToJSON End

} // namespace debug
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_H

