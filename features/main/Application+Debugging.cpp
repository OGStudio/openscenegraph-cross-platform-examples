FEATURE main.h/Include
#include "debug.h"

FEATURE main.h/Setup
// NOTE Do not use `-` because it breaks everything.
this->setupDebugging("OSGCPE04");

FEATURE main.h/TearDown
this->tearDebuggingDown();

FEATURE main.h/Impl
public:
    debug::Debugger *debugger;
private:
    const std::string debuggerCallbackName = "Debugger";

    void setupDebugging(const std::string &name)
    {
        this->debugger = new debug::Debugger(this->httpClient, name);
        this->debugger->setBrokerURL("https://osgcpe-debug-broker.herokuapp.com");

        // Subscribe debugger to be processed each frame.
        this->frameReporter.addCallback(
            [&] {
                this->debugger->process();
            },
            this->debuggerCallbackName
        );
    }
    void tearDebuggingDown()
    {
        // Unsubscribe debugger.
        this->frameReporter.removeCallback(this->debuggerCallbackName);
        delete this->debugger;
    }
