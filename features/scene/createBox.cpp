FEATURE scene.h/Impl
osg::MatrixTransform *createBox(const osg::Vec3f &size)
{
    auto box = new osg::Box(osg::Vec3f(0, 0, 0), size.x(), size.y(), size.z());
    return createShape(box);
}
osg::MatrixTransform *createBox(float size)
{
    return createBox(osg::Vec3f(size, size, size));
}
