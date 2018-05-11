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

        auto page = this->pages.begin();
        for (; page != this->pages.end(); ++page)
        {
            log::log("Page");
            auto json = debug::pageToJSON(*page);
            log::log(json.c_str());
        }
        // TODO construct JSON out of all pages.
        // TODO send JSON.
    }
    // TODO process with FetchAPI.
    // TODO receive JSON?
