FEATURE main.cpp/Include
#include "core.h"
#include "main.h"
#include <emscripten.h>
#include <SDL2/SDL.h>

FEATURE main.cpp/Loop
// We use Example global variable in loop() function.
main::Example *example = 0;

// Stand alone function that is called by Emscripten to run the app.
void loop()
{
    if (example)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            example->app->handleEvent(e);
        }
        example->app->frame();
    }
}

FEATURE main.cpp/Setup
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
        osgcpe::EXAMPLE_TITLE,
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
// Create example.
example = new main::Example;
example->app->setupWindow(width, height);

FEATURE main.cpp/Run
// Render asynchronously.
emscripten_set_main_loop(loop, -1, 0);
