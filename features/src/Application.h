
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H

// FEATURE Application+Logging/Include
// FEATURE Application+Rendering/Include

namespace osgcpe
{

class Application
{
    public:
        Application(const std::string &name)
        {
            // FEATURE Application+Logging/Setup
            // FEATURE Application+Rendering/Setup
        }
        ~Application()
        {
            // FEATURE Application+Rendering/TearDown
            // FEATURE Application+Logging/TearDown
        }

        // FEATURE Application+run/Impl
        // FEATURE Application+setupWindow-desktop/Impl
        // FEATURE Application+setupWindow-embedded/Impl

        // FEATURE Application+Logging/Impl
        // FEATURE Application+Rendering/Impl
};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H

