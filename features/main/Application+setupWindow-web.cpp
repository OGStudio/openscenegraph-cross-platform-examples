FEATURE main.h/Include
#include <SDL2/SDL.h>

FEATURE main.h/Impl
private:
    SDL_Window *sdlWindow = 0;
public:
    bool setupWindow(
        const std::string &title,
        int width,
        int height
    ) {
        this->configureSDLGLContext();
        this->sdlWindow =
            SDL_CreateWindow(
                title.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                width,
                height,
                SDL_WINDOW_OPENGL
            );
        if (!this->sdlWindow)
        {
            MAIN_APPLICATION_LOG(
                "ERROR Could not create SDL window: '%s'\n",
                SDL_GetError()
            );
            return false;
        }

        SDL_GL_CreateContext(this->sdlWindow);
        this->setupWindow(width, height);

        return true;
    }
    void configureSDLGLContext()
    {
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    }
