
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_INPUT_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_INPUT_H

// Mouse Start
#include "core.h"
#include <algorithm>
#include <osgGA/GUIEventHandler>

// Mouse End


namespace osgcpe
{
namespace input
{

// MouseButtons Start
//! NOTE Mobile platforms only have LEFT button.
enum MOUSE_BUTTON
{
    MOUSE_BUTTON_NONE,
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,
};

//! Convert OSG key index to mouse button enum value.
MOUSE_BUTTON indexToMouseButton(int index)
{
    switch (index)
    {
        case osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON:
            return MOUSE_BUTTON_LEFT;
        case osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON:
            return MOUSE_BUTTON_MIDDLE;
        case osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON:
            return MOUSE_BUTTON_RIGHT;
        default:
            return MOUSE_BUTTON_NONE;
    }
}

//! Convert mouse button enum value to string representation.
const char *mouseButtonToString(MOUSE_BUTTON button)
{
    switch (button)
    {
        case MOUSE_BUTTON_LEFT:
            return "MOUSE_BUTTON_LEFT";
        case MOUSE_BUTTON_RIGHT:
            return "MOUSE_BUTTON_RIGHT";
        case MOUSE_BUTTON_MIDDLE:
            return "MOUSE_BUTTON_MIDDLE";
        default:
            return "MOUSE_BUTTON_NONE";
    }
}
// MouseButtons End
// Mouse Start
//! Handle OpenSceneGraph mouse events.
class Mouse : public osgGA::GUIEventHandler
{
    public:
        Mouse() : position(0, 0) { }

        // Current mouse position.
        osg::Vec2f position;
        core::Reporter positionChanged;

        // Currently pressed mouse buttons.
        std::vector<MOUSE_BUTTON> pressedButtons;
        core::Reporter pressedButtonsChanged;

        bool handle(
            const osgGA::GUIEventAdapter &eventAdapter,
            osgGA::GUIActionAdapter &actionAdapter,
            osg::Object *object,
            osg::NodeVisitor *visitor
        ) override {
            // Report mouse position if changed.
            osg::Vec2f pos(eventAdapter.getX(), eventAdapter.getY());
            if (this->position != pos)
            {
                this->position = pos;
                this->positionChanged.report();
                INPUT_MOUSE_LOG("Position: '%f x %f'", pos.x(), pos.y());
            }

            // Process pressed buttons.
            bool isPressed = false;
            if (eventAdapter.getEventType() == osgGA::GUIEventAdapter::PUSH)
            {
                isPressed = true;
            }
            else if (eventAdapter.getEventType() == osgGA::GUIEventAdapter::RELEASE)
            {
                // Do nothing.
            }
            else
            {
                return true;
            }
            auto button = indexToMouseButton(eventAdapter.getButton());
            this->setButtonState(button, isPressed);
            return true;
        }

    private:
        void setButtonState(MOUSE_BUTTON button, bool state)
        {
            auto &buttons = this->pressedButtons;
            auto btn = std::find(buttons.begin(), buttons.end(), button);
            // Button is already pressed.
            if (btn != buttons.end())
            {
                // Release button.
                if (!state)
                {
                    buttons.erase(
                        std::remove(buttons.begin(), buttons.end(), button),
                        buttons.end()
                    );
                    this->pressedButtonsChanged.report();
                    //OSGCPE_INPUT_MOUSE_LOG("Released button '%d'", button);
                }
            }
            // Button is not pressed.
            else
            {
                // Push button.
                if (state)
                {
                    buttons.push_back(button);
                    this->pressedButtonsChanged.report();
                    //OSGCPE_INPUT_MOUSE_LOG("Pressed button '%d'", button);
                }
            }
        }
};
// Mouse End

} // namespace input
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_INPUT_H

