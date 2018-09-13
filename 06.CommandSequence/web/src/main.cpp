
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

// main-web Start
#include "main.h"
#include <emscripten.h>
#include <SDL2/SDL.h>

// main-web End

using namespace osgcpe;

// main-web Start
// Declare global example to be used by free functions.
main::Example *example = 0;

// Stand alone function that is called by Emscripten to run the app.
void loop()
{
    if (example)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {

// main-web End
// main-web Start
        }
        example->app->frame();
    }
}

// main-web End

int main(int argc, char *argv[])
{

    // main-web Start
    // Make sure SDL is working.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("ERROR Could not initialize SDL: '%s'\n", SDL_GetError());
        return 1;
    }
    // Clean SDL up at exit.
    atexit(SDL_Quit);
    
    main::Example::Parameters parameters;
    
    // main-web End
    // main-web Start
    example = new main::Example(parameters);
    // Create rendering window of initial size.
    if (!example->app->setupWindow(main::EXAMPLE_TITLE, 800, 600))
    {
        return 1;
    }
    example->app->resizeWindowToCanvasSize();
    
    // main-web End

    // main-web Start
    // Render asynchronously.
    emscripten_set_main_loop(loop, -1, 0);
    // main-web End
    return 0;
}

