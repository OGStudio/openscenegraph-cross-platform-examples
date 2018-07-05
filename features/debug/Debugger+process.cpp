FEATURE debug.h/Impl
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
            //OSGCPE_DEBUG_DEBUGGER_LOG("Process JSON: '%s'", response.c_str());
            // Only process incoming JSON response if there's response
            if (response.length())
            {
                this->processJSON(response);
            }
            else
            {
                OSGCPE_DEBUG_DEBUGGER_LOG("ERROR Received empty response");
            }
            this->isProcessing = false;
        };
        auto failure = [&](std::string reason) {
            OSGCPE_DEBUG_DEBUGGER_LOG(reason.c_str());
            this->isProcessing = false;
        };
        std::string data = debuggerToJSON(this->title, this->pages);
        this->httpClient->post(this->brokerURL, data, success, failure);
    }
