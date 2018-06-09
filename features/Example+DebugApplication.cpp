FEATURE Example.h/Setup
this->setupApplicationDebugging();

FEATURE Example.h/Impl
private:
    void setupApplicationDebugging()
    {
        this->dbg->addPage(this->app->debugPage);
    }
