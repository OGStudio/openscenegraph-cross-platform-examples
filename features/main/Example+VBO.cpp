FEATURE main.h/Include
#include "render.h"

FEATURE main.h/Setup
this->setupSceneVBO();

FEATURE main.h/Impl
private:
    void setupSceneVBO()
    {
        // Do nothing for an empty scene.
        if (!this->scene.valid())
        {
            return;
        }
        // Use VBO and EBO instead of display lists.
        // CRITICAL for:
        // * mobile
        // * web (Emscripten) to skip FULL_ES2 emulation flag
        osgcpe::render::VBOSetupVisitor vbo;
        this->scene->accept(vbo);
    }
