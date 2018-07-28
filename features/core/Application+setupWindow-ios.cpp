FEATURE core.h/Impl
UIView *setupWindow(
    int width,
    int height,
    float scale,
    UIView *parentView
) {
    osgViewer::GraphicsWindowIOS *gc =
        dynamic_cast<osgViewer::GraphicsWindowIOS *>(
            render::createGraphicsContext(width, height, scale, parentView)
        );
    // Configure viewer's camera with FOVY and window size.
    osg::Camera *cam = this->viewer->getCamera();
    render::setupCamera(cam, gc, 30, width * scale, height * scale);
    // Return UIView for embedding.
    return (UIView *)gc->getView();
}
