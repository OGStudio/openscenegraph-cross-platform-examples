
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RESOURCES_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RESOURCES_H

#include "Resource.h"
#include "ResourceStreamBuffer.h"
// resources+node Start
#include <osgDB/Registry>

// resources+node End

namespace osgcpe
{
namespace resources
{

// resources+node Start
// TODO Support extension detection.
osg::ref_ptr<osg::Node> node(Resource &resource, const std::string extension)
{
    osg::ref_ptr<osg::Node> node;
    auto reader =
        osgDB::Registry::instance()->getReaderWriterForExtension(extension);
    if (reader)
    {
        ResourceStreamBuffer buf(resource);
        std::istream in(&buf);
        auto result = reader->readNode(in, 0);
        if (result.success())
        {
            node = result.getNode();
        }
        else
        {
            log::logprintf(
                "ERROR Could not read node of '%s' resource from buffer.",
                resource.name.c_str()
            );
        }
    }
    else
    {
        log::logprintf(
            "ERROR Could not read node of '%s' resource because "
            "node reader for extension '%s' is absent.",
            resource.name.c_str(),
            extension.c_str()
        );
    }
    return node.release();
}
// resources+node End

} // namespace resources
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RESOURCES_H

