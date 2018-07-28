FEATURE main.h/Impl
public:
    core::Reporter frameReporter;
    void frame()
    {
        this->viewer->frame();
        this->frameReporter.report();
    }
