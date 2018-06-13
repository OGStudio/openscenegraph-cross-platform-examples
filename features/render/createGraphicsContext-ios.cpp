FEATURE render.h/Include
#include <osgViewer/api/IOS/GraphicsWindowIOS>

FEATURE render.h/Impl
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
            0,
            osgViewer::GraphicsWindowIOS::WindowData::IGNORE_ORIENTATION
        );
    dat->setViewContentScaleFactor(scale);
    traits->inheritedWindowData = dat;
    // Create GC.
    return osg::GraphicsContext::createGraphicsContext(traits);
}
