
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

#include "Example.h"
// main-web Start
#include <emscripten.h>
#include <SDL2/SDL.h>

// main-web End
// main+FetchRegularly-web Start
#include <emscripten/fetch.h>

// main+FetchRegularly-web End

// main-web Start
// We use Example global variable in loop() function.
osgcpe::Example *example = 0;

// Stand alone function that is called by Emscripten to run the app.
void loop()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        /*
        if (example)
        {
            example->app->handleEvent(e);
        }
        */
    }
    if (example)
    {
        example->app->frame();
    }
}

// main-web End
// main+FetchRegularly-web Start
// Forward declaration.
void fetchValue();

void fetchSucceeded(emscripten_fetch_t *fetch)
{
    printf(
        "Fetch. Finished downloading '%llu' bytes from '%s'\n",
        fetch->numBytes,
        fetch->url
    );

    const int BUF_SIZE = 100;
    // Get the body.
    if (fetch->numBytes < BUF_SIZE)
    {
        char buf[BUF_SIZE];
        strncpy(buf, fetch->data, fetch->numBytes);
        buf[fetch->numBytes + 1] = '\0';
        std::string body(buf);
        printf("Fetch. Received value: '%s'\n", body.c_str());
    }
    else
    {
        printf("Fetch. Too much data. Cannot parse\n");
    }
    emscripten_fetch_close(fetch);
    // Perform new fetch.
    fetchValue();
}

void fetchFailed(emscripten_fetch_t *fetch)
{
    printf(
        "Fetch. Failed to download '%s'. HTTP status code: '%d'\n",
        fetch->url,
        fetch->status
    );
    emscripten_fetch_close(fetch);
    // Do not perform new fetches?
}

void fetchValue()
{
    // Create a request for a resource over HTTP.
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = fetchSucceeded;
    attr.onerror = fetchFailed;
    // Resource URL.
    auto url = "http://127.0.0.1:7999";
    // Perform the request.
    emscripten_fetch(&attr, url);
    printf("Fetch. Request value from '%s'\n", url);
}

// main+FetchRegularly-web End

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
    example = new osgcpe::Example;
    example->app->setupWindow(width, height);
    
    // main-web End
    // main-web Start
    // Render asynchronously.
    emscripten_set_main_loop(loop, -1, 0);
    // main-web End
    // main+FetchRegularly-web Start
    // Start regular fetching.
    fetchValue();
    // main+FetchRegularly-web End
    return 0;
}

