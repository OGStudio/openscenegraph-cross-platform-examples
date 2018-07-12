FEATURE library.h/Decl
namespace osgcpe
{
namespace network
{
class HTTPClient;
}
}

FEATURE library.h/Impl
// Return HTTP client for host to poll.
osgcpe::network::HTTPClient *httpClient();

FEATURE library.cpp/Impl
osgcpe::network::HTTPClient *httpClient()
{
    return 0;
    // TODO return example->app->httpClient;
}
