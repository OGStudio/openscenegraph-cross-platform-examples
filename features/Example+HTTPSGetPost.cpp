FEATURE Example.h/Include
#include "network.h"

FEATURE Example.h/Setup
this->setupHTTPSGetPost();

FEATURE Example.h/Impl
private:
    void setupHTTPSGetPost()
    {
        // Reset background color.
        this->app->camera()->setClearColor({ 0, 0, 0, 0 });
        // Set background color 50% greener on success.
        auto success = [&](std::string response) {
            auto color = this->app->camera()->getClearColor();
            color.y() += 0.5;
            this->app->camera()->setClearColor(color);
            OSGCPE_EXAMPLE_LOG(response.c_str());
        };
        // Set background color 50% redder on failure.
        auto failure = [&](std::string reason) {
            auto color = this->app->camera()->getClearColor();
            color.x() += 0.5;
            this->app->camera()->setClearColor(color);
            OSGCPE_EXAMPLE_LOG(reason.c_str());
        };

        // GET.
        this->app->httpClient->get(
            "https://httpbin.org/get",
            success,
            failure
        );
        // POST.
        this->app->httpClient->post(
            "https://httpbin.org/post",
            "sample-data",
            success,
            failure
        );
    }
