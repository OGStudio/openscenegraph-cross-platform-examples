
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

// quaternionToDegrees Start
osg::Vec3f quaternionToDegrees(const osg::Quat &quaternion)
{
    double q0 = quaternion.x();
    double q1 = quaternion.y();
    double q2 = quaternion.z();
    double q3 = quaternion.w();
    
    //double sq0 = q0 * q0;
    double sq1 = q1 * q1;
    double sq2 = q2 * q2;
    double sq3 = q3 * q3;
    
    double term1 = 2*(q0*q1 + q2*q3);
    double term2 = 1 - 2 * (sq1 + sq2);
    double term3 = 2 * (q0*q2 - q3*q1);
    double term4 = 2 * (q0*q3 + q1*q2);
    double term5 = 1 - 2 * (sq2 + sq3);

    double z = atan2(term1, term2);
    double y = asin(term3);
    double x = atan2(term4, term5);

    osg::Vec3f result(x * 180.0 / M_PI, y * 180.0 / M_PI, z * 180.0 / M_PI);
    // Fix for X when Y = 0.
    result.x() = 180 - result.x();
    // Fix for Z when Y = 0.
    if (result.z() < 0)
    {
        result.z() = 360 + result.z();
    }
    return result;
}
// quaternionToDegrees End
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

