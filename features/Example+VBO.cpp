FEATURE Example.h/Include
#include "VBOSetupVisitor.h"

FEATURE Example.h/Impl
// Use VBO and EBO instead of display lists. CRITICAL for web (Emscripten)
// to skip FULL_ES2 emulation flag.
osgcpe::VBOSetupVisitor vbo;
scene->accept(vbo);
