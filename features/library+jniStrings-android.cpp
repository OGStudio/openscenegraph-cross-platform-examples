FEATURE library.cpp/Impl
// Convert C++ strings to JNI ones.
jobjectArray jniStrings(JNIEnv *env, const std::vector<std::string> items)
{
    // NOTE According to https://stackoverflow.com/questions/6238785/newstringutf-and-freeing-memory
    // NOTE we don't need to free memory of New* calls because these are Java's local references.
    // NOTE Since we pass them to Java (later), we don't need to do anything about them.
    jclass stringType = env->FindClass("java/lang/String");
    jobjectArray result = env->NewObjectArray(items.size(), stringType, 0);
    int id = 0;
    for (auto item : items)
    {
        jstring jniItem = env->NewStringUTF(item.c_str());
        env->SetObjectArrayElement(result, id++, jniItem);
    }
    return result;
}
