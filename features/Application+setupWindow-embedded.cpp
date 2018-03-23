FEATURE Application.h/Impl
public:
    void setupWindow(int width, int height)
    {
        this->viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
    }
