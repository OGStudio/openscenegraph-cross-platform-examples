FEATURE Debugger.h/Include
#include <nlohmann/json.hpp>

FEATURE Debugger.h/Impl
public:
    void processJSON(const std::string &data)
    {
        // TODO Introduce debug page protocol to only deal with internal representation,
        // TODO not explict JSON parsing.
        auto jdata = nlohmann::json::parse(data);
        auto debuggerTitle = jdata["title"].get<std::string>();
        log::logprintf("processJSON. debugger title: '%s'", debuggerTitle.c_str());
        // Ignore different debuggers.
        if (debuggerTitle != this->title)
        {
            // TODO Report different debugger.
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
