FEATURE main.h/Impl
UIView *setupWindow(
    int width,
    int height,
    float scale,
    UIView *parentView
) {
    osgViewer::GraphicsWindowIOS *gc =
        dynamic_cast<osgViewer::GraphicsWindowIOS *>(
            createGraphicsContext(width, height, scale, parentView)
        );
    // Configure viewer's camera with FOVY and window size.
    osg::Camera *cam = mViewer->getCamera();
    setupCamera(cam, gc, 30, width * scale, height * scale);
    // Return UIView to embed.
    return (UIView *)gc->getView();
}

FEATURE functions.h/Include
#include <osgViewer/api/IOS/GraphicsWindowIOS>

FEATURE functions.h/Impl
// Create graphics context for iOS.
osg::GraphicsContext *createGraphicsContext(
    int width,
    int height,
    float scale,
    UIView *parentView
) {
    // Traits is a struct to combine necessary parameters.
    osg::GraphicsContext::Traits *traits =
        new osg::GraphicsContext::Traits;
    // Geometry.
    traits->x = 0;
    traits->y = 0;
    traits->width = width * scale;
    traits->height = height * scale;
    // Double buffer (simply put, it's a flicker fix).
    traits->doubleBuffer = true;
    // Parent view.
    osg::ref_ptr<osgViewer::GraphicsWindowIOS::WindowData> dat =
        new osgViewer::GraphicsWindowIOS::WindowData(
            parentView,
            osgViewer::GraphicsWindowIOS::WindowData::IGNORE_ORIENTATION
        );
    dat->setViewContentScaleFactor(scale);
    traits->inheritedWindowData = dat;
    // Create GC.
    return osg::GraphicsContext::createGraphicsContext(traits);
}
