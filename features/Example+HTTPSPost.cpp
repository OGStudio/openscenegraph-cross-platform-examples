FEATURE Example.h/Include
#include "network.h"

FEATURE Example.h/Setup
this->setupHTTPSPost();

FEATURE Example.h/Impl
private:
    void setupHTTPSPost()
    {
        auto success = [&](std::string response) {
            // Set background color to green on success.
            this->app->camera()->setClearColor({ 0, 1, 0, 0 });
            OSGCPE_EXAMPLE_LOG(response.c_str());
        };
        auto failure = [&](std::string reason) {
            // Set background color to red on failure.
            this->app->camera()->setClearColor({ 1, 0, 0, 0 });
            OSGCPE_EXAMPLE_LOG(reason.c_str());
        };
        auto url = "https://httpbin.org/post";
        this->app->httpClient->post(url, "sample-post-request", success, failure);
    }
