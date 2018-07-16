
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
// FEATURE Example+BoxScene/Include
// FEATURE Example+TextureImageScene/Include
// FEATURE Example+HTTPSGet/Include
// FEATURE Example+HTTPSPost/Include
// FEATURE Example+VBO/Include

// FEATURE Example+OSGCPE_EXAMPLE_LOG/Impl
// FEATURE Example+StaticPluginImageIO/Impl
// FEATURE Example+StaticPluginOSG/Impl
// FEATURE Example+StaticPluginPNG/Impl

namespace osgcpe
{

// FEATURE Example+01/Title
// FEATURE Example+02/Title
// FEATURE Example+03/Title
// FEATURE Example+04/Title

struct Example
{

    osgcpe::Application *app;

    Example()
    {
        this->app = new osgcpe::Application(EXAMPLE_TITLE);

        // FEATURE Example+BoxScene/Setup
        // FEATURE Example+VBO/Setup
        // FEATURE Example+SingleColorScene/Setup
        // FEATURE Example+TextureImageScene/Setup
        // FEATURE Example+BoxSelection/Setup
        // FEATURE Example+BoxRotation/Setup
        // FEATURE Example+HTTPSGet/Setup
        // FEATURE Example+HTTPSPost/Setup
    }
    ~Example()
    {
        // FEATURE Example+BoxRotation/TearDown
        // FEATURE Example+BoxSelection/TearDown

        delete this->app;
    }

    // FEATURE Example+BoxRotation/Impl
    // FEATURE Example+BoxScene/Impl
    // FEATURE Example+BoxSelection/Impl
    // FEATURE Example+HTTPSGet/Impl
    // FEATURE Example+HTTPSPost/Impl
    // FEATURE Example+SingleColorScene/Impl
    // FEATURE Example+TextureImageScene/Impl
    // FEATURE Example+VBO/Impl

};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H

