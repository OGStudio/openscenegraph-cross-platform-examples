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

OSGCPE_JNI(httpClientCompleteRequest)(
    OSGCPE_JNI_ARG,
    jstring requestId,
    jboolean status,
    jstring response
) {
    // TODO Release result of GetStringUTFChars?
    std::string sid(env->GetStringUTFChars(requestId, 0));
    intptr_t id = ::strtoll(sid.c_str(), 0, 10);
    auto request = reinterpret_cast<osgcpe::network::HTTPRequest *>(id);
    if (!request)
    {
        return;
    }
    // Report.
    request->status = osgcpe::network::HTTPRequest::COMPLETED;
    // TODO Release result of GetStringUTFChars?
    std::string reply(env->GetStringUTFChars(response, 0));
    if (status == JNI_TRUE)
    {
        request->success(reply);
    }
    else
    {
        request->failure(reply);
    }
}
