FEATURE Application.h/Include
#include "network.h"

FEATURE Application.h/Setup
this->setupHTTPClient();

FEATURE Application.h/TearDown
this->tearHTTPClientDown();

FEATURE Application.h/Impl
public:
    network::HTTPClient *httpClient;
private:
    const std::string httpClientCallbackName = "HTTPClient";

    void setupHTTPClient()
    {
        this->httpClient = new network::HTTPClient;

        // Subscribe HTTP client to be processed each frame.
        this->frameReporter.addCallback(
            [&] {
                if (this->httpClient->needsProcessing())
                {
                    this->httpClient->process();
                }
            },
            this->httpClientCallbackName
        );
    }
    void tearHTTPClientDown()
    {
        // Unsubscribe HTTP client.
        this->frameReporter.removeCallback(this->httpClientCallbackName);
        delete this->httpClient;
    }
