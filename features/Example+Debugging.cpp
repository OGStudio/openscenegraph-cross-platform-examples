FEATURE Example.h/Include
#include "HTTPClient.h"
#include "Debugger.h"

FEATURE Example.h/Setup
this->setupDebugging();

FEATURE Example.h/TearDown
this->tearDebuggingDown();

FEATURE Example.h/Impl
private:
    osgcpe::Debugger *dbg;
    osgcpe::HTTPClient *dbgHTTPClient;

    void setupDebugging()
    {
        this->dbgHTTPClient = new osgcpe::HTTPClient;
        this->dbg = new osgcpe::Debugger(this->dbgHTTPClient, EXAMPLE_TITLE);
        // TODO Heroku? Parametrize.
        this->dbg->setBrokerURL("http://localhost:7999");
    }
    void tearDebuggingDown()
    {
        delete this->dbg;
        delete this->dbgHTTPClient;
    }

