FEATURE Debugger.h/Include
#include "debug.h"
// TODO REMOVE after testing
#include <ctime>

FEATURE Debugger.h/Impl
public:
    void process()
    {
        // TODO REMOVE after testing
        // 1. Make 5s pause between consequent requests.
        static std::time_t lastProcessDt = 0;
        auto now = std::time(0);
        if (now - lastProcessDt < 5)
        {
            return;
        }
        lastProcessDt = now;
        // TODO Provide non-static flag.
        // 2. Only make new request once previous one has been completed.
        static bool finishedRequest = true;
        if (!finishedRequest)
        {
            return;
        }
        finishedRequest = false;
           
        auto callback = [&](std::string response) {
            // Process incoming JSON response.
            this->processJSON(response);
            finishedRequest = true;
        };
        log::log("process-default");
        std::string data = debug::debuggerToJSON(this->title, this->pages);
        httpClient->post(this->brokerURL, data, callback, callback);
    }
