FEATURE library.cpp/Impl
// Pop next pending request and execute it (implicitely mark it as IN_PROGRESS).
OSGCPE_JNI_ARRAY(httpClientExecuteNextRequest)(OSGCPE_JNI_ARG)
{
    std::vector<std::string> requestParts = {
        "133", // id.
        "https://httpbin.org/get", // URL.
        "" // Data. Empty means GET.
    };
    return jniStrings(env, requestParts);
    /*
    auto request = example->app->httpClient->nextPendingRequest();
    if (request)
    {
        request->status = osgcpe::network::HTTPRequest::IN_PROGRESS;
        intptr_t id = reinterpret_cast<intptr_t>(request);
        url = request->url;
        data = request->data;
    }
    */
}

