
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
// main+FullPage-web Start
#include <emscripten/html5.h>

// main+FullPage-web End

using namespace osgcpe;

// main-web Start
// We use Example global variable in loop() function.
main::Example *example = 0;

// main-web End

// main+FullPage-web Start
bool canvasSize(int *width, int *height)
{
    double w;
    double h;
    auto result = emscripten_get_element_css_size("canvas", &w, &h);

    if (result >= 0)
    {
        *width = w;
        *height = h;
        return true;
    }
    return false;
}
/*
bool handleWindowResize(const SDL_Event &e)
{
    // Make sure this is a window event.
    if (e.type != SDL_WINDOWEVENT)
    {
        return false;
    }

    // Make sure this is a resize event.
    if (e.window.event != SDL_WINDOWEVENT_RESIZED)
    {
        return false;
    }

    return;
}
*/
void resizeWindowToCanvasSize(SDL_Window *window)
{
    printf("resizeWindowToCanvasSize.01\n");
    int width;
    int height;

    // Do nothing if canvas size retrieval fails.
    if (!canvasSize(&width, &height))
    {
        return;
    }

    printf("resizeWindowToCanvasSize.02. w/h: '%d / %d'\n", width, height);
    // Resize.
    SDL_SetWindowSize(window, width, height);
    // Resize render window.
    example->app->setupWindow(width, height);
}
EM_BOOL windowResized(
    int eventType,
    const EmscriptenUiEvent *event,
    void *userData
) {
    printf("windowResized.01\n");
    int width;
    int height;

    // Do nothing if canvas size retrieval fails.
    if (!canvasSize(&width, &height))
    {
        return EM_FALSE;
    }

    printf("windowResized.02. w/h: '%d / %d'\n", width, height);
    // Resize render window.
    example->app->setupWindow(width, height);

    return EM_TRUE;
}
// main+FullPage-web End

// main-web Start
// Stand alone function that is called by Emscripten to run the app.
void loop()
{
    if (example)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {

// main-web End
            // main+Input-web Start
            example->app->handleEvent(e);
            // main+Input-web End
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
        printf("Could not init SDL: '%s'\n", SDL_GetError());
        return 1;
    }
    // Clean SDL up at exit.
    atexit(SDL_Quit);
    // Configure rendering context.
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // Create rendering window.
    int width = 800;
    int height = 600;
    
    SDL_Window* window =
        SDL_CreateWindow(
            main::EXAMPLE_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_OPENGL);
    if (!window)
    {
        printf("Could not create window: '%s'\n", SDL_GetError());
        return 1;
    }
    
    SDL_GL_CreateContext(window);
    main::Example::Parameters parameters;
    
    // main-web End
    // main-web Start
    example = new main::Example(parameters);
    example->app->setupWindow(width, height);
    
    // main-web End
    // main+FullPage-web Start
    emscripten_set_resize_callback("canvas", 0, 0, windowResized);
    resizeWindowToCanvasSize(window);
    
    // main+FullPage-web End

    // main-web Start
    // Render asynchronously.
    emscripten_set_main_loop(loop, -1, 0);
    // main-web End
    return 0;
}
