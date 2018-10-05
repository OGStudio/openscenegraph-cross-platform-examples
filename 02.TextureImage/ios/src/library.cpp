
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

#include "missing-functions-android.h"

#include "main.h"
// library-ios Start
#include "library.h"

// library-ios End


using namespace osgcpe;

// Example instance.
main::Example *example = 0;

// library-ios Start
namespace library
{

// library-ios End

// library+init-ios Start
UIView *init(int width, int height, float scale, UIView *parentView)
{
    // Create example only once.
    // If we create example at stack, the instance might get initialized
    // before plugin readers/writers are available, which would break everything.
    if (!example)
    {
        main::Example::Parameters parameters;
        example = new main::Example(parameters);
    }
    return example->app->setupWindow(width, height, scale, parentView);
}
// library+init-ios End
// library+frame-ios Start
void frame()
{
    example->app->frame();
}
// library+frame-ios End


// library-ios Start
} // namespace library.
// library-ios End

