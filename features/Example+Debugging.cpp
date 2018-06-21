FEATURE Example.h/Include
#include "debug.h"

FEATURE Example.h/Setup
this->setupDebugging();

FEATURE Example.h/TearDown
this->tearDebuggingDown();

FEATURE Example.h/Impl
private:
    debug::Debugger *dbg;
    const std::string debuggerCallbackName = "Debugger";

    void setupDebugging()
    {
        this->dbg = new debug::Debugger(this->httpClient, EXAMPLE_TITLE);
        this->dbg->setBrokerURL("https://osgcpe-debug-broker.herokuapp.com");

        // Subscribe debugger to be processed each frame.
        this->app->frameReporter.addCallback(
            [&] {
                this->dbg->process();
            },
            this->debuggerCallbackName
        );
    }
    void tearDebuggingDown()
    {
        // Unsubscribe debugger.
        this->app->frameReporter.removeCallback(this->debuggerCallbackName);
        delete this->dbg;
    }
