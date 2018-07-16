
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_LIBRARY_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_LIBRARY_H

// library+init-ios Start
// Forward declare UIView for Objective-C++ and C++.
#ifdef __OBJC__
    @class UIView;
#else
    class UIView;
#endif

// library+init-ios End
// library+httpClient-ios Start
#include <string>

// library+httpClient-ios End

namespace library
{

// library+frame-ios Start
// Rendering.
void frame();

// library+frame-ios End
// library+init-ios Start
// Initialization.
UIView *init(int width, int height, float scale, UIView *parentView);

// library+init-ios End

// library+httpClient-ios Start
intptr_t httpClientExecuteNextRequest(std::string &url, std::string &data);
void httpClientCompleteRequest(
    intptr_t id,
    bool status,
    const std::string &reply
);

// library+httpClient-ios End

} // namespace library.

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_LIBRARY_H

