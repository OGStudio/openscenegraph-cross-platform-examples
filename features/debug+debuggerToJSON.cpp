FEATURE debug.h/Impl
std::string debuggerToJSON(
    const std::string &debuggerTitle, 
    const std::vector<DebugPage> &pages
) {
    std::string pagesJSON = "";
    for (auto page = pages.begin(); page != pages.end(); ++page)
    {
        // Add comma if we're adding the second and following pages.
        if (!pagesJSON.empty())
        {
            pagesJSON += ",";
        }
        pagesJSON += debug::pageToJSON(*page);
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

