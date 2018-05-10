FEATURE Example.h/Include
#include "Debugger.h"

FEATURE Example.h/Setup
this->setupDebugging();

FEATURE Example.h/TearDown
this->tearDebuggingDown();

FEATURE Example.h/Impl
private:
    osgcpe::Debugger *dbg;

    void setupDebugging()
    {
        this->dbg = new osgcpe::Debugger;
        this->dbg->setConsoleURL("https://remote-debugger.herokuapp.com");
        // TODO: add debugger to polling or global queue...
    }
    void tearDebuggingDown()
    {
        delete this->dbg;
    }

