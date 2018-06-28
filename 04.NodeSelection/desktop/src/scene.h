
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCENE_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCENE_H

// textureImageScene Start
#include "resource.h"

// textureImageScene End

namespace osgcpe
{
namespace scene
{

// textureImageScene Start
void textureImageScene(
    const resource::Resource &shaderFrag,
    const resource::Resource &shaderVert,
    const resource::Resource &textureImage,
    osg::Node *scene
) {
    // Create shader program.
    auto prog =
        render::createShaderProgram(
            resource::string(shaderVert),
            resource::string(shaderFrag)
        );
    // Apply the program.
    auto material = scene->getOrCreateStateSet();
    material->setAttribute(prog);
    // Set texture image.
    material->setTextureAttributeAndModes(0, resource::createTexture(textureImage));
    material->addUniform(new osg::Uniform("image", 0));
}
// textureImageScene End


} // namespace scene
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCENE_H

