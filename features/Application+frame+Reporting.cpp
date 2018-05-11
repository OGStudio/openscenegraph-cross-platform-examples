FEATURE Application.h/Include
#include "Reporter.h"

FEATURE Application.h/Impl
public:
    Reporter frameReporter;
    void frame()
    {
        this->viewer->frame();
        this->frameReporter.report();
    }
