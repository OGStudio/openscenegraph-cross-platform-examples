FEATURE Application.h/Include
#include "input.h"

FEATURE Application.h/Setup
this->setupMouse();

FEATURE Application.h/TearDown
this->tearMouseDown();

FEATURE Application.h/Impl
public:
    input::Mouse *mouse;
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
