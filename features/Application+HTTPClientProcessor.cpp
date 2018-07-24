FEATURE Application.h/Setup
this->setupHTTPClientProcessor();

FEATURE Application.h/TearDown
this->tearHTTPClientProcessorDown();

FEATURE Application.h/Impl
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
