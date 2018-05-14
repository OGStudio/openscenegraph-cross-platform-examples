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
        this->dbg = new osgcpe::Debugger(EXAMPLE_TITLE);
        this->dbg->setConsoleURL("https://remote-debugger.herokuapp.com");
    }
    void tearDebuggingDown()
    {
        delete this->dbg;
    }

