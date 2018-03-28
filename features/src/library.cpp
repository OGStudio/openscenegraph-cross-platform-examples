
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
// FEATURE library+BoxScene/Include
// FEATURE library+VBO/Include

// FEATURE library+OSGCPE_LIBRARY_LOG/Impl
// FEATURE library+StaticPluginOSG/Impl

struct LibraryApplication
{
    osgcpe::Application *app;

    LibraryApplication()
    {
        // FEATURE library+Ex01/Name
        this->app = new osgcpe::Application(appName);
        // FEATURE library+ReaderWriterDebug/Impl
        // FEATURE library+BoxScene/Impl
        if (scene.valid())
        {
            // FEATURE library+VBO/Impl
            osgcpe::scene::paintScene(scene);
            this->app->setScene(scene);
        }
    }
};

// Library application instance.
LibraryApplication libapp;

namespace library
{

UIView *init(int width, int height, float scale, UIView *parentView)
{
    return libapp.app->setupWindow(width, height, scale, parentView);
}

void frame()
{
    libapp.app->frame();
}

} // namespace library.

