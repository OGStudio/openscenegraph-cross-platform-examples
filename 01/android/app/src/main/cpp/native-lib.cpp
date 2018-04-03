#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring

JNICALL
Java_org_opengamestudio_ex01_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



#define OSGCPE_JNI(FUNC_NAME) \
    JNIEXPORT void JNICALL Java_org_opengamestudio_ex01_library_ ## FUNC_NAME
 
#define OSGCPE_JNI_ARG JNIEnv *env, jobject /* this */

extern "C" {

//! Setup graphics context.
OSGCPE_JNI(init)(OSGCPE_JNI_ARG, jint width, jint height)
{
    osgcpe::library::app.setupWindow(width, height);
}

//! Rendering.
OSGCPE_JNI(step)(OSGCPE_JNI_ARG)
{
    osgcpe::library::app.frame();
}

} // extern "C".

