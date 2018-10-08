
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

// library-android Start
#include "missing-functions-android.h"
#include <jni.h>

// library-android End
#include "main.h"

// library+Ex01+JNI-android Start
#define JNI_FUNC(FUNC_NAME) \
    JNIEXPORT void JNICALL Java_org_opengamestudio_ex01_library_ ## FUNC_NAME
#define JNI_ARG JNIEnv *env, jobject /* this */
// library+Ex01+JNI-android End

using namespace osgcpe;

// Example instance.
main::Example *example = 0;

// library-android Start
extern "C" {

// library-android End

// library+init-android Start
// Setup graphics context.
JNI_FUNC(init)(JNI_ARG, jint width, jint height)
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
JNI_FUNC(frame)(JNI_ARG)
{
    example->app->frame();
}

// library+frame-android End


// library-android Start
} // extern "C".

// library-android End

