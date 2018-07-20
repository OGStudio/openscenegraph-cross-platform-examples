FEATURE library.cpp/Include
#include "format.h"

FEATURE library.cpp/Impl
// Pop next pending request and execute it (implicitely mark it as IN_PROGRESS).
OSGCPE_JNI_ARRAY(httpClientExecuteNextRequest)(OSGCPE_JNI_ARG)
{
    std::vector<std::string> requestParts;
    auto request = example->app->httpClient->nextPendingRequest();
    if (request)
    {
        request->status = osgcpe::network::HTTPRequest::IN_PROGRESS;
        intptr_t id = reinterpret_cast<intptr_t>(request);
        std::string sid = osgcpe::format::printfString("%ld", id);
        requestParts.push_back(sid);
        requestParts.push_back(request->url);
        requestParts.push_back(request->data);
    }
    return jniStrings(env, requestParts);
}

