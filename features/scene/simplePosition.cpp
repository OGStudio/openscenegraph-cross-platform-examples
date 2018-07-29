FEATURE scene.h/Include
#include <osg/MatrixTransform>

FEATURE scene.h/Impl
//! Get node position.
//! NOTE Only works for non-rotated/scaled nodes.
osg::Vec3f simplePosition(osg::MatrixTransform *node)
{
    return node->getMatrix().getTrans();
}
