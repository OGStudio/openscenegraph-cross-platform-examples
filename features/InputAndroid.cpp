FEATURE main.h/Impl
void moveMouse(float x, float y)
{
    mViewer->getEventQueue()->mouseMotion(x, y);
}
void pressMouse(bool down, float x, float y)
{
    int mmb = 2;
    if (down)
        mViewer->getEventQueue()->mouseButtonPress(x, y, mmb);
    else
        mViewer->getEventQueue()->mouseButtonRelease(x, y, mmb);
}
