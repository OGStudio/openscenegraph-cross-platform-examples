FEATURE Application.h/Impl
private:
    int windowWidth;
    int windowHeight;
public:
    void setupWindow(int width, int height)
    {
        this->viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
        this->windowWidth = width;
        this->windowHeight = height;
    }
