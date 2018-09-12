FEATURE main.cpp/Include
#include <emscripten/html5.h>

FEATURE main.cpp/Loop
handleWindowResize(e);

FEATURE main.cpp/Setup
resizeWindowToCanvasSize();

FEATURE main.cpp/Impl
bool canvasSize(int *width, int *height)
{
    double w;
    double h;
    auto result = emscripten_get_element_css_size("canvas", &w, &h);

    if (result >= 0)
    {
        *width = w;
        *height = h;
        return true;
    }
    return false;
}
void resizeWindowToCanvasSize()
{
    printf("resizeWindowToCanvasSize.01\n");
    int width;
    int height;

    // Do nothing if canvas size retrieval fails.
    if (!canvasSize(&width, &height))
    {
        return;
    }

    printf("resizeWindowToCanvasSize.02. w/h: '%d / %d'\n", width, height);

    // Do nothing if size is the same.
    int oldWidth;
    int oldHeight;
    SDL_GetWindowSize(window, &oldWidth, &oldHeight);
    if (
        width == oldWidth &&
        height == oldHeight
    ) {
        return;
    }

    // Resize SDL window.
    SDL_SetWindowSize(window, width, height);
    // Resize OSG window.
    example->app->setupWindow(width, height);
}
bool handleWindowResize(const SDL_Event &e)
{
    // Make sure this is a window event.
    if (e.type != SDL_WINDOWEVENT)
    {
        return false;
    }

    printf("got window event\n");

    // Make sure this is a resize event.
    bool isResized = (e.window.event == SDL_WINDOWEVENT_RESIZED);
    bool isSizeChanged = (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED);
    if (!isResized && !isSizeChanged)
    {
        return false;
    }

    resizeWindowToCanvasSize();

    return true;
}
