FEATURE main.h/Include
#include "script.h"

FEATURE main.h/Setup
this->setupScriptingTest();

FEATURE main.h/TearDown
this->tearScriptingTestDown();

FEATURE main.h/Impl
private:
    script::Environment *environment;
    void setupScriptingTest()
    {
        this->environment = new script::Environment;
    }
    void tearScriptingTestDown()
    {
        delete this->environment;
    }
