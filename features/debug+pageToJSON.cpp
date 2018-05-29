FEATURE debug.h/Include
#include "DebugPage.h"

FEATURE debug.h/Impl
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

