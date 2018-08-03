
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

// osgPlugins-osg-desktop Start
#include <osgDB/Registry>
// Serializers.
USE_SERIALIZER_WRAPPER(Group)
USE_SERIALIZER_WRAPPER(Object)
USE_SERIALIZER_WRAPPER(Node)
#include "src/osgWrappers/serializers/osg/Group.cpp"
#include "src/osgWrappers/serializers/osg/Object.cpp"
#include "src/osgWrappers/serializers/osg/Node.cpp"

extern "C" void wrapper_serializer_library_osg(void) {}
// osgPlugins-osg-desktop End
