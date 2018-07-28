FEATURE core.h/Impl
public:
    Reporter frameReporter;
    void frame()
    {
        this->viewer->frame();
        this->frameReporter.report();
    }
