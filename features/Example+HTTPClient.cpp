FEATURE Example.h/Include
#include "network.h"

FEATURE Example.h/Setup
this->setupHTTPClient();

FEATURE Example.h/TearDown
this->tearHTTPClientDown();

FEATURE Example.h/Impl
private:
    network::HTTPClient *httpClient;
    const std::string httpClientCallbackName = "HTTPClient";

    void setupHTTPClient()
    {
        this->httpClient = new network::HTTPClient;

        // Subscribe HTTP client to be processed each frame.
        this->app->frameReporter.addCallback(
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
        this->app->frameReporter.removeCallback(this->httpClientCallbackName);
        delete this->httpClient;
    }
