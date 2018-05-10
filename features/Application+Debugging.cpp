FEATURE Application.h/Include
#include "DebugPage.h"

FEATURE Application.h/Setup
this->setupDebugging();

FEATURE Application.h/Impl
public:
    DebugPage debugPage;

    void setupDebugging()
    {
        this->debugPage.title = "camera";
    }
