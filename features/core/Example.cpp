FEATURE core.h/Include
#include "scene.h"

FEATURE core.h/Setup
struct Example
{
    core::Application *app;

    Example()
    {
        this->app = new core::Application(EXAMPLE_TITLE);

FEATURE core.h/TearDown
    }
    ~Example()
    {

FEATURE core.h/Impl
        delete this->app;
    }

FEATURE core.h/End
};
