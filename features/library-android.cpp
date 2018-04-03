FEATURE library.cpp/Include
#include <jni.h>

FEATURE library.cpp/NamespaceStart
#define OSGCPE_JNI(FUNC_NAME) \
    JNIEXPORT void JNICALL Java_org_opengamestudio_ex01_library_ ## FUNC_NAME
#define OSGCPE_JNI_ARG JNIEnv *env, jobject /* this */

extern "C" {

FEATURE library.cpp/NamespaceEnd
} // extern "C".

