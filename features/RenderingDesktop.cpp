FEATURE main.h/Impl
void run()
{
    mViewer->run();
}
void setupWindow(
    const std::string &title,
    int x,
    int y,
    int width,
    int height)
{
    osg::GraphicsContext *gc =
        createGraphicsContext(title, x, y, width, height);
    // Configure viewer's camera with FOVY and window size.
    osg::Camera *cam = mViewer->getCamera();
    setupCamera(cam, gc, 30, width, height);
}

FEATURE functions.h/Impl
// Create graphics context for Linux, macOS, Windows.
osg::GraphicsContext *createGraphicsContext(
    const std::string &title,
    int x,
    int y,
    int width,
    int height)
{
    // Traits is a struct to combine necessary parameters.
    osg::GraphicsContext::Traits *traits =
        new osg::GraphicsContext::Traits;
    // Geometry.
    traits->x = x;
    traits->y = y;
    traits->width = width;
    traits->height = height;
    // Title.
    traits->windowName = title;
    // Window borders.
    traits->windowDecoration = true;
    // Double buffer (simply put, it's a flicker fix).
    traits->doubleBuffer = true;
    // Create GC.
    return osg::GraphicsContext::createGraphicsContext(traits);
}
