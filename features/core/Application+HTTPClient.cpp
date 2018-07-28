FEATURE core.h/Include
#include "network.h"

FEATURE core.h/Setup
this->setupHTTPClient();

FEATURE core.h/TearDown
this->tearHTTPClientDown();

FEATURE core.h/Impl
public:
    network::HTTPClient *httpClient;
private:
    void setupHTTPClient()
    {
        this->httpClient = new network::HTTPClient;
    }
    void tearHTTPClientDown()
    {
        delete this->httpClient;
    }
