
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "main.h"
// library-android Start
#include <jni.h>

// library-android End
// library+httpClient-android Start
#include "format.h"

// library+httpClient-android End

// library+Ex04+OSGCPE_JNI-android Start
#define OSGCPE_JNI(FUNC_NAME) \
    JNIEXPORT void JNICALL Java_org_opengamestudio_ex04_library_ ## FUNC_NAME
#define OSGCPE_JNI_ARRAY(FUNC_NAME) \
    JNIEXPORT jobjectArray JNICALL Java_org_opengamestudio_ex04_library_ ## FUNC_NAME
#define OSGCPE_JNI_ARG JNIEnv *env, jobject /* this */
// library+Ex04+OSGCPE_JNI-android End

using namespace osgcpe;

// Example instance.
main::Example *example = 0;

// library-android Start
extern "C" {

// library-android End

// library+init-android Start
// Setup graphics context.
OSGCPE_JNI(init)(OSGCPE_JNI_ARG, jint width, jint height)
{
    // Create example only once.
    // If we create example at stack, the instance might get initialized
    // before plugin readers/writers are available, which would break everything.
    if (!example)
    {
        main::Example::Parameters parameters;
        example = new main::Example(parameters);
    }
    return example->app->setupWindow(width, height);
}
// library+init-android End
// library+frame-android Start
// Rendering.
OSGCPE_JNI(frame)(OSGCPE_JNI_ARG)
{
    example->app->frame();
}

// library+frame-android End
// library+jniStrings-android Start
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
// library+jniStrings-android End

// library+httpClient-android Start
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
    // Get request id.
    const char *cid = env->GetStringUTFChars(requestId, 0);
    std::string sid(cid);
    intptr_t id = ::strtoll(sid.c_str(), 0, 10);
    env->ReleaseStringUTFChars(requestId, cid);

    // Try to get request from id.
    auto request = reinterpret_cast<osgcpe::network::HTTPRequest *>(id);
    if (!request)
    {
        return;
    }

    // Report result of the request.
    request->status = osgcpe::network::HTTPRequest::COMPLETED;
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
// library+httpClient-android End

// library-android Start
} // extern "C".

// library-android End

