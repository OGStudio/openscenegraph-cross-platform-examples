FEATURE library.cpp/Impl
// Pop next pending request and execute it (implicitely mark it as IN_PROGRESS).
OSGCPE_JNI_ARRAY(httpClientExecuteNextRequest)(OSGCPE_JNI_ARG)
{
    std::vector<std::string> requestParts = {
        "133", // id.
        "https://httpbin.org/get", // URL.
        "" // Data. Empty means GET.
    };
    jclass stringType = env->FindClass("java/lang/String");
    jobjectArray requestState =
        env->NewObjectArray(requestParts.size(), stringType, 0);
    int id = 0;
    for (auto requestPart : requestParts)
    {
        jstring part = env->NewStringUTF(requestPart.c_str());
        env->SetObjectArrayElement(requestState, id++, part);
    }
    return requestState;
}

