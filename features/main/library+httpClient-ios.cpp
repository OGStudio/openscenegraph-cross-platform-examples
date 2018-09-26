FEATURE library.h/Include
#include <string>

FEATURE library.h/Impl
intptr_t httpClientExecuteNextRequest(std::string &url, std::string &data);
void httpClientCompleteRequest(
    intptr_t id,
    bool status,
    const std::string &reply
);

FEATURE library.cpp/Impl
// Pop next pending request and execute it (implicitely mark it as IN_PROGRESS).
intptr_t httpClientExecuteNextRequest(std::string &url, std::string &data)
{
    auto request = example->app->httpClient->nextPendingRequest();
    if (request)
    {
        request->status = network::HTTPRequest::IN_PROGRESS;
        url = request->url;
        data = request->data;
    }
    return reinterpret_cast<intptr_t>(request);
}

void httpClientCompleteRequest(
    intptr_t id,
    bool status,
    const std::string &reply
) {
    auto request = reinterpret_cast<network::HTTPRequest *>(id);
    if (!request)
    {
        return;
    }
    // Report.
    request->status = network::HTTPRequest::COMPLETED;
    if (status)
    {
        request->success(reply);
    }
    else
    {
        request->failure(reply);
    }
}
