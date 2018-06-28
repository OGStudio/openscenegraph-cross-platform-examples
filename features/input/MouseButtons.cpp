FEATURE input.h/Impl
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
