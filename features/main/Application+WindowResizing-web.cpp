FEATURE main.h/Include
#include <emscripten/html5.h>

FEATURE main.h/Setup
this->setupWindowResizing();

FEATURE main.h/Impl
public:
    void resizeWindowToCanvasSize()
    {
        // Do nothing if canvas size retrieval fails.
        int width;
        int height;
        if (!canvasSize(&width, &height))
        {
            return;
        }

        // Do nothing if size is the same.
        int currentWidth;
        int currentHeight;
        SDL_GetWindowSize(this->sdlWindow, &currentWidth, &currentHeight);
        if (
            width == currentWidth &&
            height == currentHeight
        ) {
            return;
        }

        // Resize SDL window.
        SDL_SetWindowSize(this->sdlWindow, width, height);
        // Resize OSG window.
        this->setupWindow(width, height);
    }
private:
    void setupWindowResizing()
    {
        emscripten_set_resize_callback(
            0,
            this,
            EM_FALSE,
            Application::resizeWindow
        );
    }
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
    static EM_BOOL resizeWindow(int, const EmscriptenUiEvent *, void *userData)
    {
        Application *app = reinterpret_cast<Application *>(userData);

        // Make sure application instance exists.
        if (!app)
        {
            return EM_FALSE;
        }

        app->resizeWindowToCanvasSize();
        return EM_TRUE;
    }
