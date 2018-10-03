
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

// main-desktop Start
#include "main.h"

// main-desktop End

using namespace osgcpe;


int main(int argc, char *argv[])
{
    // main-desktop Start
    main::Example::Parameters parameters;
    
    // main-desktop End
    // main-desktop Start
    auto example = new main::Example(parameters);
    example->app->setupWindow(main::EXAMPLE_TITLE, 100, 100, 480, 320);
    
    // main-desktop End


    // main-desktop Start
    example->app->run();
    delete example;
    // main-desktop End
    return 0;
}

