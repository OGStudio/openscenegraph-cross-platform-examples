FEATURE library.cpp/Include
#include "format.h"

FEATURE library.cpp/Impl
// Pop next pending request and execute it (implicitely mark it as IN_PROGRESS).
JNI_FUNC_ARRAY(httpClientExecuteNextRequest)(JNI_ARG)
{
    std::vector<std::string> requestParts;
    auto request = example->app->httpClient->nextPendingRequest();
    if (request)
    {
        request->status = network::HTTPRequest::IN_PROGRESS;
        intptr_t id = reinterpret_cast<intptr_t>(request);
        std::string sid = format::printfString("%ld", id);
        requestParts.push_back(sid);
        requestParts.push_back(request->url);
        requestParts.push_back(request->data);
    }
    return jniStrings(env, requestParts);
}

JNI_FUNC(httpClientCompleteRequest)(
    JNI_ARG,
    jstring requestId,
    jboolean status,
    jstring response
) {
    // Get request id.
    const char *cid = env->GetStringUTFChars(requestId, 0);
    std::string sid(cid);
    intptr_t id = ::strtoll(sid.c_str(), 0, 10);
    env->ReleaseStringUTFChars(requestId, cid);

    // Try to get request from id.
    auto request = reinterpret_cast<network::HTTPRequest *>(id);
    if (!request)
    {
        return;
    }

    // Report result of the request.
    request->status = network::HTTPRequest::COMPLETED;
    const char *creply = env->GetStringUTFChars(response, 0);
    std::string reply(creply);
    if (status == JNI_TRUE)
    {
        request->success(reply);
    }
    else
    {
        request->failure(reply);
    }
    env->ReleaseStringUTFChars(response, creply);
}
