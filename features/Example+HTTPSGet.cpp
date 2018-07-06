FEATURE Example.h/Include
#include "network.h"

FEATURE Example.h/Setup
this->setupHTTPSGet();

FEATURE Example.h/Impl
private:
    void setupHTTPSGet()
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
        this->app->httpClient->get("https://github.com/OGStudio", success, failure);
    }
