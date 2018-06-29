FEATURE scene.h/Include
#include <osg/MatrixTransform>

FEATURE scene.h/Impl
//! Get node rotation.
osg::Vec3f simpleRotation(osg::MatrixTransform *node)
{
    auto quat = node->getMatrix().getRotate();
    return quaternionToDegrees(quat);
}
