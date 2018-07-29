FEATURE scene.h/Impl
//! Set node position.
//! NOTE Only works for non-rotated/scaled nodes.
void setSimplePosition(osg::MatrixTransform *node, const osg::Vec3f &position)
{
    auto matrix = node->getMatrix();
    node->setMatrix(
        osg::Matrix::scale(matrix.getScale()) *
        osg::Matrix::rotate(matrix.getRotate()) *
        osg::Matrix::translate(position)
    );
}
