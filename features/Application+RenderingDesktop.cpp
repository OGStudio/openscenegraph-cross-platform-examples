FEATURE Application.h/Impl
public:
    void run()
    {
        this->viewer->run();
    }
    void setupWindow(
        const std::string &title,
        int x,
        int y,
        int width,
        int height
    ) {
        osg::GraphicsContext *gc =
            createGraphicsContext(title, x, y, width, height);
        // Configure viewer's camera with FOVY and window size.
        osg::Camera *cam = this->viewer->getCamera();
        setupCamera(cam, gc, 30, width, height);
    }

