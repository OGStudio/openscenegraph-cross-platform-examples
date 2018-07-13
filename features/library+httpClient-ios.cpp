FEATURE library.h/Include
#include <string>

FEATURE library.h/Impl
int httpClientNextPendingRequest(std::string &url, std::string &data);

FEATURE library.cpp/Impl
int httpClientNextPendingRequest(std::string &url, std::string &data)
{
    // TODO Do real calls.

    url = "http://your.domain.test";
    data = "{\"key\": \"value\"}";

    return 144;
}
