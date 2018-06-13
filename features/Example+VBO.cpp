FEATURE Example.h/Include
#include "render.h"

FEATURE Example.h/Impl
// Use VBO and EBO instead of display lists. CRITICAL for web (Emscripten)
// to skip FULL_ES2 emulation flag.
osgcpe::render::VBOSetupVisitor vbo;
scene->accept(vbo);
