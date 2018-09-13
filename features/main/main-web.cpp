FEATURE main.cpp/Include
#include "main.h"
#include <emscripten.h>
#include <SDL2/SDL.h>

FEATURE main.cpp/LoopBegin
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

FEATURE main.cpp/LoopEnd
        }
        example->app->frame();
    }
}

FEATURE main.cpp/Setup
// Make sure SDL is working.
if (SDL_Init(SDL_INIT_VIDEO) < 0)
{
    printf("ERROR Could not initialize SDL: '%s'\n", SDL_GetError());
    return 1;
}
// Clean SDL up at exit.
atexit(SDL_Quit);

main::Example::Parameters parameters;

FEATURE main.cpp/End
example = new main::Example(parameters);
// Create rendering window of initial size.
if (!example->app->setupWindow(main::EXAMPLE_TITLE, 800, 600))
{
    return 1;
}

FEATURE main.cpp/Run
// Render asynchronously.
emscripten_set_main_loop(loop, -1, 0);
