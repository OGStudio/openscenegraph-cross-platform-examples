FEATURE Debugger.h/Include
#include "debug.h"

FEATURE Debugger.h/Impl
public:
    void process()
    {
        // Only run once to debug first.
        static bool runOnce = true;
        if (!runOnce)
        {
            return;
        }
        runOnce = false;
        log::log("process-web");

        std::string pagesJSON = "";

        auto page = this->pages.begin();
        for (; page != this->pages.end(); ++page)
        {
            // Add comma if we're adding the second and following pages.
            if (!pagesJSON.empty())
            {
                pagesJSON += ",";
            }
            pagesJSON += debug::pageToJSON(*page);
        }

        // Format pages.
        std::string json;
        json += "{";

        json += "\"title\":\"";
        json += this->title;
        json += "\",";

        json += "\"pages\":[";
        json += pagesJSON;
        json += "]"; // Note the absent comma.

        json += "}";

        log::log("All pages");
        log::log(json.c_str());
        // TODO send JSON.
    }
    // TODO process with FetchAPI.
    // TODO receive JSON?
