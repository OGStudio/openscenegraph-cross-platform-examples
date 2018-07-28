FEATURE main.h/Include
#include "input.h"

FEATURE main.h/Setup
this->setupMouse();

FEATURE main.h/TearDown
this->tearMouseDown();

FEATURE main.h/Impl
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
        // This also removes Mouse instance.
        this->viewer->removeEventHandler(this->mouse);
    }
