FEATURE scene.h/Impl
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
