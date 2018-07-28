FEATURE core.h/Include
#include "input.h"

FEATURE core.h/Setup
this->setupMouse();

FEATURE core.h/TearDown
this->tearMouseDown();

FEATURE core.h/Impl
public:
    osg::ref_ptr<input::Mouse> mouse;
private:
    void setupMouse()
    {
        // Create mouse events' handler.
        this->mouse = new input::Mouse;
        // Register it.
        this->viewer->addEventHandler(this->mouse);
    }
    void tearMouseDown()
    {
        OSGCPE_APPLICATION_LOG("tearMouseDown.01");
        // This also removes Mouse instance.
        this->viewer->removeEventHandler(this->mouse);
        OSGCPE_APPLICATION_LOG("tearMouseDown.02");
    }
