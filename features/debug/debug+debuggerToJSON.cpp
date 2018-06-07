FEATURE debug.h/Include
#include <string>
#include <vector>

FEATURE debug.h/Impl
std::string debuggerToJSON(
    const std::string &debuggerTitle, 
    const std::vector<Page> &pages
) {
    std::string pagesJSON = "";
    for (auto page : pages)
    {
        // Add comma if we're adding the second and following pages.
        if (!pagesJSON.empty())
        {
            pagesJSON += ",";
        }
        pagesJSON += pageToJSON(page);
    }

    // Format debugger.
    std::string json;
    json += "{";

    json += "\"title\":\"";
    json += debuggerTitle;
    json += "\",";

    json += "\"pages\":[";
    json += pagesJSON;
    json += "]"; // Note the absent comma.

    json += "}";

    return json;
}
