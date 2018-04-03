
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

#include "Application.h"
#include "scene.h"
// main-web Start
#include <emscripten.h>
#include <SDL2/SDL.h>

// main-web End
// main+BoxScene Start
#include "box.osgt.h"
#include "resources.h"

// main+BoxScene End
// main+VBO Start
#include "VBOSetupVisitor.h"

// main+VBO End

// main+OSGCPE_MAIN_LOG Start
#include "log.h"
#define OSGCPE_MAIN_LOG_PREFIX "osgcpe-main %s"
#define OSGCPE_MAIN_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_MAIN_LOG_PREFIX, \
        osgcpe::log::printfString(__VA_ARGS__).c_str() \
    )

// main+OSGCPE_MAIN_LOG End
// main+StaticPluginOSG Start
// Reference plugins to read `osgt` file statically.
USE_OSGPLUGIN(osg2)
USE_SERIALIZER_WRAPPER_LIBRARY(osg)
// main+StaticPluginOSG End
// main-web Start
// We use app global variable in loop() function.
osgcpe::Application *app = 0;

// Stand alone function that is called by Emscripten to run the app.
void loop()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        /*
        if (app)
        {
            app->handleEvent(e);
        }
        */
    }
    if (app)
    {
        app->frame();
    }
}

// main-web End

int main(int argc, char *argv[])
{
    // main+Ex01 Start
    auto appName = "Ex01";
    // main+Ex01 End

    // main-web Start
    // Make sure SDL is working.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        OSGCPE_MAIN_LOG("Could not init SDL: '%s'\n", SDL_GetError());
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
            appName,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_OPENGL);
    if (!window)
    {
        OSGCPE_MAIN_LOG("Could not create window: '%s'\n", SDL_GetError());
        return 1;
    }
    SDL_GL_CreateContext(window);
    // Create application.
    app = new osgcpe::Application(appName);
    app->setupWindow(width, height);
    
    // main-web End
    // main+BoxScene Start
    osgcpe::Resource box("models", "box.osgt", box_osgt, box_osgt_len);
    auto scene = osgcpe::resources::node(box);
    if (!scene.valid())
    {
        OSGCPE_MAIN_LOG("ERROR Could not load scene");
    }
    // main+BoxScene End
    if (scene.valid())
    {
        // main+VBO Start
        // Use VBO and EBO instead of display lists. CRITICAL for web (Emscripten)
        // to skip FULL_ES2 emulation flag.
        osgcpe::VBOSetupVisitor vbo;
        scene->accept(vbo);
        // main+VBO End
        osgcpe::scene::paintScene(scene);
        app->setScene(scene);
    }
    // main-web Start
    // Render asynchronously.
    emscripten_set_main_loop(loop, -1, 0);
    // main-web End
    return 0;
}

