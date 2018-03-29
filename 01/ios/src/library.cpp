
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
#include "library.h"
#include "scene.h"
// library+BoxScene Start
#include "box.osgt.h"
#include "resources.h"

// library+BoxScene End
// library+VBO Start
#include "VBOSetupVisitor.h"

// library+VBO End

// library+OSGCPE_LIBRARY_LOG Start
#include "log.h"
#define OSGCPE_LIBRARY_LOG_PREFIX "osgcpe-library %s"
#define OSGCPE_LIBRARY_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_LIBRARY_LOG_PREFIX, \
        osgcpe::log::printfString(__VA_ARGS__).c_str() \
    )

// library+OSGCPE_LIBRARY_LOG End
// library+StaticPluginOSG Start
// Reference plugins to read `osgt` files.
USE_OSGPLUGIN(osg2)
USE_SERIALIZER_WRAPPER_LIBRARY(osg)
// library+StaticPluginOSG End

struct LibraryApplication
{
    osgcpe::Application *app;

    LibraryApplication()
    {
        // library+Ex01 Start
        auto appName = "Ex01";
        // library+Ex01 End
        this->app = new osgcpe::Application(appName);
        // library+ReaderWriterDebug Start
        auto registry = osgDB::Registry::instance();
        auto list = registry->getReaderWriterList();
        OSGCPE_LIBRARY_LOG("ReaderWriterList size: '%d'", list.size());
        // library+ReaderWriterDebug End
        // library+BoxScene Start
        osgcpe::Resource box("models", "box.osgt", box_osgt, box_osgt_len);
        auto scene = osgcpe::resources::node(box);
        if (!scene.valid())
        {
            OSGCPE_LIBRARY_LOG("ERROR Could not load scene");
        }
        // library+BoxScene End
        if (scene.valid())
        {
            // library+VBO Start
            // Use VBO and EBO instead of display lists. CRITICAL for web (Emscripten)
            // to skip FULL_ES2 emulation flag.
            osgcpe::VBOSetupVisitor vbo;
            scene->accept(vbo);
            // library+VBO End
            osgcpe::scene::paintScene(scene);
            this->app->setScene(scene);
        }
    }
};

// Library application instance.
LibraryApplication *libapp = 0;

namespace library
{

UIView *init(int width, int height, float scale, UIView *parentView)
{
    // Create library application only once.
    // If we create library application at stack, the instance might get initialized
    // before plugin readers/writers are available, which would break everything.
    if (!libapp)
    {
        libapp = new LibraryApplication;
    }
    return libapp->app->setupWindow(width, height, scale, parentView);
}

void frame()
{
    libapp->app->frame();
}

} // namespace library.

