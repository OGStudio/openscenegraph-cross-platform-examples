FEATURE rendering.h/Include
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>

FEATURE rendering.h/Impl
osg::MatrixTransform *createShape(osg::Shape *shape) {
    auto *hints = new osg::TessellationHints;
    hints->setDetailRatio(0.5);
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->addDrawable(new osg::ShapeDrawable(shape, hints));
    osg::ref_ptr<osg::MatrixTransform> node = new osg::MatrixTransform;
    node->addChild(geode);
    return node.release();
}

osg::MatrixTransform *createBox(const osg::Vec3f &size)
{
    auto *box = new osg::Box(osg::Vec3f(0, 0, 0), size.x(), size.y(), size.z());
    return createShape(box);
}

osg::MatrixTransform *createBox(float width)
{
    return createBox(osg::Vec3f(width, width, width));
}

