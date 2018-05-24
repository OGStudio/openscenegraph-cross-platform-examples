FEATURE Debugger.h/Include
#include "debug.h"
// TODO REMOVE after testing
#include <ctime>

FEATURE Debugger.h/Impl
public:
    void process()
    {
        // TODO REMOVE after testing
        // Only report once in 5 seconds.
        static std::time_t lastProcessDt = 0;
        auto now = std::time(0);
        if (now - lastProcessDt < 5)
        {
            return;
        }
        lastProcessDt = now;

        log::log("process-default");
        std::string json = this->stateAsJSON();
        auto callback = [&](std::string response){
            log::logprintf("process callback response: '%s'", response.c_str());
        };
        httpClient->post(this->brokerURL, json, callback, callback);
    }
    // TODO receive JSON?
