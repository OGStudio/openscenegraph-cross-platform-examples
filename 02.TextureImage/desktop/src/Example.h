
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H
        
#include "Application.h"
#include "scene.h"
// Example+BoxScene Start
#include "box.osgt.h"
#include "resources.h"

// Example+BoxScene End

// Example+OSGCPE_EXAMPLE_LOG Start
#include "log.h"
#define OSGCPE_EXAMPLE_LOG_PREFIX "osgcpe-example(%p) %s"
#define OSGCPE_EXAMPLE_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_EXAMPLE_LOG_PREFIX, \
        this, \
        osgcpe::log::printfString(__VA_ARGS__).c_str() \
    )

// Example+OSGCPE_EXAMPLE_LOG End

namespace osgcpe
{

// Example+02 Start
const auto EXAMPLE_TITLE = "Ex02";
// Example+02 End

struct Example
{

    osgcpe::Application *app;

    Example()
    {
        this->app = new osgcpe::Application(EXAMPLE_TITLE);
        // Example+BoxScene Start
        osgcpe::Resource box("models", "box.osgt", box_osgt, box_osgt_len);
        auto scene = osgcpe::resources::node(box);
        if (!scene.valid())
        {
            OSGCPE_EXAMPLE_LOG("ERROR Could not load scene");
        }
        // Example+BoxScene End
        if (scene.valid())
        {
            this->app->setScene(scene);
        }
    }
    ~Example()
    {
        delete this->app;
    }

};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H

