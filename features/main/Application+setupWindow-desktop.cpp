FEATURE main.h/Impl
public:
    void setupWindow(
        const std::string &title,
        int x,
        int y,
        int width,
        int height
    ) {
        osg::GraphicsContext *gc =
            render::createGraphicsContext(title, x, y, width, height);
        // Configure viewer's camera with FOVY and window size.
        osg::Camera *cam = this->viewer->getCamera();
        render::setupCamera(cam, gc, 30, width, height);
    }
