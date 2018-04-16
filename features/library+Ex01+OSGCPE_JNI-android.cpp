FEATURE library.cpp/Impl
#define OSGCPE_JNI(FUNC_NAME) \
    JNIEXPORT void JNICALL Java_org_opengamestudio_ex01_library_ ## FUNC_NAME
#define OSGCPE_JNI_ARG JNIEnv *env, jobject /* this */
