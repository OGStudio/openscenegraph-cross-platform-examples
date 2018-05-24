
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
// Example+TextureImageScene Start
#include "resources.h"
#include "ppl.frag.h"
#include "ppl.vert.h"
#include "digit.png.h"

// Example+TextureImageScene End
// Example+Debugging Start
#include "HTTPClient.h"
#include "Debugger.h"

// Example+Debugging End

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

// Example+03 Start
const auto EXAMPLE_TITLE = "Ex03";
// Example+03 End

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
            // Example+TextureImageScene Start
            osgcpe::Resource shaderFrag("shaders", "ppl.frag", ppl_frag, ppl_frag_len);
            osgcpe::Resource shaderVert("shaders", "ppl.vert", ppl_vert, ppl_vert_len);
            osgcpe::Resource textureImage("images", "digit.png", digit_png, digit_png_len);
            osgcpe::scene::textureImageScene(shaderFrag, shaderVert, textureImage, scene);
            // Example+TextureImageScene End
            this->app->setScene(scene);
        }
        // Example+Debugging Start
        this->setupDebugging();
        
        // Example+Debugging End
        // Example+DebugApplication Start
        this->setupApplicationDebugging();
        
        // Example+DebugApplication End
    }
    ~Example()
    {
        // Example+Debugging Start
        this->tearDebuggingDown();
        
        // Example+Debugging End
        // Example+DebugApplication Start
        this->tearApplicationDebuggingDown();
        
        // Example+DebugApplication End
        delete this->app;
    }

    // Example+Debugging Start
    private:
        osgcpe::Debugger *dbg;
        osgcpe::HTTPClient *dbgHTTPClient;
    
        void setupDebugging()
        {
            this->dbgHTTPClient = new osgcpe::HTTPClient;
            this->dbg = new osgcpe::Debugger(this->dbgHTTPClient, EXAMPLE_TITLE);
            // TODO Heroku?
            this->dbg->setBrokerURL("http://localhost:7999");
        }
        void tearDebuggingDown()
        {
            delete this->dbg;
            delete this->dbgHTTPClient;
        }
    
    // Example+Debugging End
    // Example+DebugApplication Start
    private:
        void setupApplicationDebugging()
        {
            this->app->frameReporter.addCallback(
                [&] {
                    this->dbg->process();
                },
                "Debug"
            );
            this->dbg->addDebugPage(this->app->debugPage);
        }
        void tearApplicationDebuggingDown()
        {
            this->app->frameReporter.removeCallback("Debug");
        }
    
    // Example+DebugApplication End

};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H

