FEATURE main.h/Impl
bool handleEvent(SDL_Event &e)
{
    osgViewer::GraphicsWindow *gw =
        dynamic_cast<osgViewer::GraphicsWindow *>(
            mViewer->getCamera()->getGraphicsContext());
    if (!gw)
    {
        return false;
    }
    osgGA::EventQueue &queue = *(gw->getEventQueue());
    switch (e.type)
    {
        case SDL_MOUSEMOTION:
            queue.mouseMotion(e.motion.x, e.motion.y);
            return true;
        case SDL_MOUSEBUTTONDOWN:
            queue.mouseButtonPress(e.button.x, e.button.y, e.button.button);
            printf("OSG. Application. Mouse button down\n");
            return true;
        case SDL_MOUSEBUTTONUP:
            queue.mouseButtonRelease(e.button.x, e.button.y, e.button.button);
            printf("OSG. Application. Mouse button up\n");
            return true;
        default:
            break;
    }
    return false;
}
