FEATURE main.cpp/Include
#include "main.h"
#include <emscripten.h>
#include <SDL2/SDL.h>

FEATURE main.cpp/Decl
// Declare globals to be used by free functions.
// TODO Create some struct/class to encapsulate both functions and variables?
main::Example *example = 0;
SDL_Window *window = 0;

FEATURE main.cpp/LoopBegin
// Stand alone function that is called by Emscripten to run the app.
void loop()
{
    if (example)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {

FEATURE main.cpp/LoopEnd
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

window =
    SDL_CreateWindow(
        main::EXAMPLE_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );
if (!window)
{
    printf("Could not create window: '%s'\n", SDL_GetError());
    return 1;
}

SDL_GL_CreateContext(window);
main::Example::Parameters parameters;

FEATURE main.cpp/End
example = new main::Example(parameters);
example->app->setupWindow(width, height);

FEATURE main.cpp/Run
// Render asynchronously.
emscripten_set_main_loop(loop, -1, 0);
