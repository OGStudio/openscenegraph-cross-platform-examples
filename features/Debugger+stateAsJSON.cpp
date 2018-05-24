FEATURE Debugger.h/Impl
private:
    std::string stateAsJSON()
    {
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

        // Format debugger.
        std::string json;
        json += "{";

        json += "\"title\":\"";
        json += this->title;
        json += "\",";

        json += "\"pages\":[";
        json += pagesJSON;
        json += "]"; // Note the absent comma.

        json += "}";

        return json;
    }
