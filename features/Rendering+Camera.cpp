FEATURE rendering.h/Impl
#include <osg/Camera>

// Configure camera with common defaults.
void setupCamera(
    osg::Camera *cam,
    osg::GraphicsContext *gc,
    double fovy,
    int width,
    int height
) {
    // Provide GC.
    cam->setGraphicsContext(gc);
    // Viewport must have the same size.
    cam->setViewport(new osg::Viewport(0, 0, width, height));
    // Clear depth and color buffers each frame.
    cam->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // Aspect ratio.
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    // Configure projection.
    cam->setProjectionMatrixAsPerspective(fovy, aspect, 1, 1000);
}
