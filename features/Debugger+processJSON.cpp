FEATURE Debugger.h/Include
#include <nlohmann/json.hpp>

FEATURE Debugger.h/Impl
public:
    void processJSON(const std::string &data)
    {
        // TODO Work with DebugPageDesc here instead of raw JSON?
        auto jdata = nlohmann::json::parse(data);
        auto debuggerTitle = jdata["title"].get<std::string>();
        // Ignore different debuggers.
        if (debuggerTitle != this->title)
        {
            OSGCPE_DEBUGGER_LOG("WARNING Ignoring debugger with different title");
            return;
        }
        auto jpages = jdata["pages"];
        for (auto jpage : jpages)
        {
            auto pageDesc = debug::jsonToPageDesc(jpage);
            auto page = this->page(pageDesc.title);
            if (page)
            {
                page->setDesc(pageDesc);
            }
        }
    }
