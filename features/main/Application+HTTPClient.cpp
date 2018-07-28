FEATURE main.h/Include
#include "network.h"

FEATURE main.h/Setup
this->setupHTTPClient();

FEATURE main.h/TearDown
this->tearHTTPClientDown();

FEATURE main.h/Impl
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
