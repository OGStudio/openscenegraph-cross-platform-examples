FEATURE main.cpp/Include
#include "VBOSetupVisitor.h"

FEATURE main.cpp/Impl
// Use VBO and EBO instead of display lists. CRITICAL for web (Emscripten)
// to skip FULL_ES2 emulation flag.
osgcpe::VBOSetupVisitor vbo;
scene->accept(vbo);
