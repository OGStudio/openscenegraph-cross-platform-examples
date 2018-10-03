
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

// simpleRotation Start
#include <osg/MatrixTransform>

// simpleRotation End
// textureImageScene Start
#include "render.h"
#include "resource.h"

// textureImageScene End


namespace osgcpe
{
namespace scene
{


// degreesToQuaternion Start
//! Convert from degrees to quaternion.
osg::Quat degreesToQuaternion(const osg::Vec3f &degrees)
{
    osg::Quat q;
    q.makeRotate(
        osg::DegreesToRadians(degrees.x()), osg::Vec3(1, 0, 0),
        osg::DegreesToRadians(degrees.y()), osg::Vec3(0, 1, 0),
        osg::DegreesToRadians(degrees.z()), osg::Vec3(0, 0, 1)
    );
    return q;
}
// degreesToQuaternion End
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
// setSimpleRotation Start
//! Set node rotation.
void setSimpleRotation(osg::MatrixTransform *node, const osg::Vec3f &rotation)
{
    osg::Quat quat = degreesToQuaternion(rotation);
    node->setMatrix(
        osg::Matrix::scale(node->getMatrix().getScale()) *
        osg::Matrix::rotate(quat) *
        osg::Matrix::translate(node->getMatrix().getTrans())
    );
}
// setSimpleRotation End
// simpleRotation Start
//! Get node rotation.
osg::Vec3f simpleRotation(osg::MatrixTransform *node)
{
    auto quat = node->getMatrix().getRotate();
    return quaternionToDegrees(quat);
}
// simpleRotation End

// nodeAtPosition Start
//! Pick node at the specified position using camera's point of view

// \param excludedNodeMask Take the node into consideration if it excludes specified mask.
osg::Node *nodeAtPosition(
    const osg::Vec2f &position,
    osg::Camera *camera,
    unsigned int excludedNodeMask
) {
    // Find intersections.
    osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
        new osgUtil::LineSegmentIntersector(
            osgUtil::Intersector::WINDOW,
            position.x(),
            position.y()
        );
    osgUtil::IntersectionVisitor iv(intersector.get());
    camera->accept(iv);

    // No intersections found.
    if (!intersector->containsIntersections())
    {
        return 0;
    }

    // Get closest intersection.
    auto intersection = intersector->getFirstIntersection();
    for (auto node : intersection.nodePath)
    {
        // Make sure node mask is excluded.
        if ((node->getNodeMask() & excludedNodeMask) != excludedNodeMask)
        {
            return node;
        }
    }

    return 0;
}
// nodeAtPosition End

// textureImageScene Start
void textureImageScene(
    osg::Node *scene,
    const resource::Resource &shaderFrag,
    const resource::Resource &shaderVert,
    const resource::Resource &textureImage
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

// LinearInterpolator Start
//! Interpolate key:value pairs linearly.

//! You would generally use time stamps as keys to provide smooth motion interpolation.
//! NOTE requirements:
//! * the keys MUST be sorted in ascending order
//! * keyValues MUST have at least two items
class LinearInterpolator
{
    public:
        LinearInterpolator() { }

        struct KeyValue
        {
            // This constructor is necessary for operator<
            // to work for floats and KeyValues at the same time.
            KeyValue(float key): key(key), value(0) { }
            KeyValue(float key, float value): key(key), value(value) { }

            float key;
            float value;

            bool operator<(const KeyValue &other) const
            {
                return this->key < other.key;
            }
        };

        std::vector<KeyValue> keyValues;

        float valueFor(float key)
        {
            // Return edge value when requested value for keys outside
            // interpolated range.
            // First item.
            auto first = this->keyValues.front();
            if (key <= first.key)
            {
                return first.value;
            }
            // Last item.
            auto last = this->keyValues.back();
            if (key >= last.key)
            {
                return last.value;
            }

            // NOTE Interpolation code is based on this sample:
            // NOTE https://bulldozer00.com/2016/05/10/linear-interpolation-in-c/

            // Find item with the key less than requested one.
            auto it =
                std::lower_bound(
                    this->keyValues.begin(),
                    this->keyValues.end(),
                    key
                );
            // Interpolate.
            float upperX = it->key;
            float upperY = it->value;
            float lowerX = (it - 1)->key;
            float lowerY = (it - 1)->value;
            float dx = upperX - lowerX;
            float dy = upperY - lowerY;

            return lowerY + ((key - lowerX) / dx) * dy;
        }
};

// LinearInterpolator End

} // namespace scene
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCENE_H

