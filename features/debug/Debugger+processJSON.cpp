FEATURE debug.h/Impl
public:
    void processJSON(const std::string &data)
    {
        // TODO Work with PageDesc here instead of raw JSON?
        auto jdata = nlohmann::json::parse(data);
        auto debuggerTitle = jdata["title"].get<std::string>();
        // Ignore different debuggers.
        if (debuggerTitle != this->title)
        {
            DEBUG_DEBUGGER_LOG("WARNING Ignoring debugger with different title");
            return;
        }
        auto jpages = jdata["pages"];
        for (auto jpage : jpages)
        {
            auto pageDesc = jsonToPageDesc(jpage);
            auto page = this->page(pageDesc.title);
            if (page)
            {
                page->setDesc(pageDesc);
            }
        }
    }
