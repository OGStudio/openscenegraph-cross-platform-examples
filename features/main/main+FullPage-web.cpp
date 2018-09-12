FEATURE main.cpp/Include
#include <emscripten/html5.h>

FEATURE main.cpp/Setup
emscripten_set_resize_callback("canvas", 0, 0, windowResized);
resizeWindowToCanvasSize(window);

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
/*
bool handleWindowResize(const SDL_Event &e)
{
    // Make sure this is a window event.
    if (e.type != SDL_WINDOWEVENT)
    {
        return false;
    }

    // Make sure this is a resize event.
    if (e.window.event != SDL_WINDOWEVENT_RESIZED)
    {
        return false;
    }

    return;
}
*/
void resizeWindowToCanvasSize(SDL_Window *window)
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
    // Resize.
    SDL_SetWindowSize(window, width, height);
    // Resize render window.
    example->app->setupWindow(width, height);
}
EM_BOOL windowResized(
    int eventType,
    const EmscriptenUiEvent *event,
    void *userData
) {
    printf("windowResized.01\n");
    int width;
    int height;

    // Do nothing if canvas size retrieval fails.
    if (!canvasSize(&width, &height))
    {
        return EM_FALSE;
    }

    printf("windowResized.02. w/h: '%d / %d'\n", width, height);
    // Resize render window.
    example->app->setupWindow(width, height);

    return EM_TRUE;
}
