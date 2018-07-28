FEATURE main.h/Impl
public:
    void handleMousePress(bool down, float x, float y)
    {
        auto queue = this->viewer->getEventQueue();
        float correctedY = (this->windowHeight - y);
        if (down)
        {
            queue->mouseButtonPress(x, correctedY, 1 /* LMB */);
        }
        else
        {
            queue->mouseButtonRelease(x, correctedY, 1 /* LMB */);
        }
    }
