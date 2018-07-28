FEATURE main.h/Setup
this->setupHTTPClientProcessor();

FEATURE main.h/TearDown
this->tearHTTPClientProcessorDown();

FEATURE main.h/Impl
public:
    network::HTTPClientProcessor *httpClientProcessor;
private:
    const std::string httpClientProcessorCallbackName = "HTTPClientProcessor";

    void setupHTTPClientProcessor()
    {
        this->httpClientProcessor = new network::HTTPClientProcessor(this->httpClient);
        // Subscribe processor to be processed each frame.
        this->frameReporter.addCallback(
            [&] {
                this->httpClientProcessor->process();
            },
            this->httpClientProcessorCallbackName
        );
    }
    void tearHTTPClientProcessorDown()
    {
        this->frameReporter.removeCallback(this->httpClientProcessorCallbackName);
        delete this->httpClientProcessor;
    }
