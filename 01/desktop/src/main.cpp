
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
// main+BoxScene Start
#include "box.osgt.h"
#include "resources.h"

// main+BoxScene End

// main+OSGCPE_MAIN_LOG Start
#include "log.h"
#define OSGCPE_MAIN_LOG_PREFIX "osgcpe-main %s"
#define OSGCPE_MAIN_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_MAIN_LOG_PREFIX, \
        osgcpe::log::printfString(__VA_ARGS__).c_str() \
    )

// main+OSGCPE_MAIN_LOG End

int main(int argc, char *argv[])
{
    // main+Ex01 Start
    auto appName = "Ex01";
    // main+Ex01 End

    // main-desktop Start
    auto app = new osgcpe::Application(appName);
    app->setupWindow(appName, 100, 100, 1024, 768);
    
    // main-desktop End
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
        osgcpe::scene::paintScene(scene);
        app->setScene(scene);
    }
    // main-desktop Start
    app->run();
    delete app;
    // main-desktop End
    return 0;
}

