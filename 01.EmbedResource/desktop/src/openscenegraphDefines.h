
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_OPENSCENEGRAPH_DEFINES_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_OPENSCENEGRAPH_DEFINES_H

// defines-desktop Start

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#ifndef APIENTRY
    #define APIENTRY
#endif

#ifndef GL_APIENTRY
    #define GL_APIENTRY APIENTRY
#endif

#define OSG_EXPORT

/*
#define OSG_GL1_AVAILABLE
#define OSG_GL2_AVAILABLE
#define OSG_GL_DISPLAYLISTS_AVAILABLE
#define OSG_GL_MATRICES_AVAILABLE
#define OSG_GL_VERTEX_FUNCS_AVAILABLE
#define OSG_GL_VERTEX_ARRAY_FUNCS_AVAILABLE
#define OSG_GL_FIXED_FUNCTION_AVAILABLE
#define GL_HEADER_HAS_GLINT64
#define GL_HEADER_HAS_GLUINT64

#define OSG_GL1_FEATURES 1
#define OSG_GL2_FEATURES 1
#define OSG_GL3_FEATURES 0
#define OSG_GLES1_FEATURES 0
#define OSG_GLES2_FEATURES 0
#define OSG_GLES3_FEATURES 0
#define OSG_GL_CONTEXT_VERSION "1.0"
*/

// defines-desktop End

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_OPENSCENEGRAPH_DEFINES_H

