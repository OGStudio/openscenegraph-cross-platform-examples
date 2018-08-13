FEATURE main.h/Include
#include <SDL2/SDL.h>

FEATURE main.h/Impl
private:
    bool fingerEventsDetected = false;
public:
    bool handleEvent(const SDL_Event &e)
    {
        // Get event queue.
        osgViewer::GraphicsWindow *gw =
            dynamic_cast<osgViewer::GraphicsWindow *>(
                this->viewer->getCamera()->getGraphicsContext());
        if (!gw)
        {
            return false;
        }
        osgGA::EventQueue &queue = *(gw->getEventQueue());

        // Detect finger events.
        if (
            e.type == SDL_FINGERMOTION ||
            e.type == SDL_FINGERDOWN ||
            e.type == SDL_FINGERUP
        ) {
            this->fingerEventsDetected = true;
        }
        // Handle mouse events unless finger events are detected.
        if (!this->fingerEventsDetected)
        {
            return this->handleMouseEvent(e, queue);
        }
        // Handle finger events.
        return this->handleFingerEvent(e, queue);
    }

private:
    bool handleFingerEvent(const SDL_Event &e, osgGA::EventQueue &queue)
    {
        int absX = this->windowWidth * e.tfinger.x;
        int absY = this->windowHeight * e.tfinger.y;
        auto correctedY = -(this->windowHeight - absY);
        switch (e.type)
        {
            case SDL_FINGERMOTION:
                queue.mouseMotion(absX, correctedY);
                return true;
            case SDL_FINGERDOWN: 
                queue.mouseButtonPress(absX, correctedY, e.tfinger.fingerId);
                return true;
            case SDL_FINGERUP:
                queue.mouseButtonRelease(absX, correctedY, e.tfinger.fingerId);
                return true;
            default:
                break;
        }
        return false;
    }

    bool handleMouseEvent(const SDL_Event &e, osgGA::EventQueue &queue)
    {
        switch (e.type)
        {
            case SDL_MOUSEMOTION: {
                auto correctedY = -(this->windowHeight - e.motion.y);
                queue.mouseMotion(e.motion.x, correctedY);
                return true;
            }
            case SDL_MOUSEBUTTONDOWN: {
                auto correctedY = -(this->windowHeight - e.button.y);
                queue.mouseButtonPress(e.button.x, correctedY, e.button.button);
                return true;
            }
            case SDL_MOUSEBUTTONUP: {
                auto correctedY = -(this->windowHeight - e.button.y);
                queue.mouseButtonRelease(e.button.x, correctedY, e.button.button);
                return true;
            }
            default:
                break;
        }
        return false;
    }
