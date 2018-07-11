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
    void setupHTTPClient()
    {
        this->httpClient = new network::HTTPClient;
    }
    void tearHTTPClientDown()
    {
        delete this->httpClient;
    }
