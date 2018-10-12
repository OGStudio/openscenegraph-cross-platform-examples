FEATURE input.h/Include
#include "core.h"
#include <algorithm>
#include <osgGA/GUIEventHandler>

FEATURE input.h/Impl
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
