FEATURE Example.h/Setup
this->setupApplicationDebugging();

FEATURE Example.h/TearDown
this->tearApplicationDebuggingDown();

FEATURE Example.h/Impl
private:
    void setupApplicationDebugging()
    {
        this->app->frameReporter.addCallback(
            [&] {
                this->dbg->process();
                if (this->dbgHTTPClient->needsProcessing())
                {
                    this->dbgHTTPClient->process();
                }
            },
            "Debug"
        );
        this->dbg->addDebugPage(this->app->debugPage);
    }
    void tearApplicationDebuggingDown()
    {
        this->app->frameReporter.removeCallback("Debug");
    }

