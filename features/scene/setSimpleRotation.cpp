FEATURE scene.h/Impl
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
