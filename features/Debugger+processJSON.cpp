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
            auto pageTitle = jpage["title"].get<std::string>();
            log::logprintf("processJSON. page title: '%s'", pageTitle.c_str());
            auto jitems = jpage["items"];
            for (auto jitem : jitems)
            {
                auto itemTitle = jitem["title"].get<std::string>();
                log::logprintf("processJSON. item title: '%s'", itemTitle.c_str());

            }

        }
        
        /*
        auto incomingPages = debug::jsonToDebugPages(this->title);
        for (auto incomingPage : incomingPages)
        {
            for (auto page : this->pages)
            {
                if (page.title == incomingPage.title)
                {
                    page.processItems(page.items);
                }
            }
        }
        */
    }
