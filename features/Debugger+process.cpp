FEATURE Debugger.h/Include
#include "debug.h"
#include <ctime>

FEATURE Debugger.h/Impl
private:
    // Request frequency control.
    std::time_t lastProcessDt = 0;
    const int processPause = 1; // In seconds.
    // Request sequencing.
    bool isProcessing = false;
public:
    void process()
    {
        // 1. Make sure `processPause` number of seconds passed since last `process()` execution.
        auto now = std::time(0);
        if (now - this->lastProcessDt < this->processPause)
        {
            return;
        }
        this->lastProcessDt = now;

        // 2. Only make new request once previous one has been completed.
        if (this->isProcessing)
        {
            return;
        }
        this->isProcessing = true;
           
        auto success = [&](std::string response) {
            //OSGCPE_DEBUGGER_LOG("Process JSON: '%s'", response.c_str());
            // Process incoming JSON response.
            this->processJSON(response);
            this->isProcessing = false;
        };
        auto failure = [&](std::string reason) {
            OSGCPE_DEBUGGER_LOG(reason.c_str());
            this->isProcessing = false;
        };
        std::string data = debug::debuggerToJSON(this->title, this->pages);
        httpClient->post(this->brokerURL, data, success, failure);
    }
