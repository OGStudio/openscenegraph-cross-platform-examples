
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCENE_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCENE_H


namespace osgcpe
{
namespace scene
{

// paintScene Start
void paintScene(osg::Node *scene)
{
    // Fragment shader to display everything in red colour.
    const char shaderFragment[] = "void main() { gl_FragColor = vec4(0.5, 0.3, 0.3, 1.0); }";
    // Vertex shader to pass geometry vertices to fragment shader.
    const char shaderVertex[] = "void main() { gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; }";
    auto prog = render::createShaderProgram(shaderVertex, shaderFragment);
    scene->getOrCreateStateSet()->setAttribute(prog);
}
// paintScene End


} // namespace scene
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_SCENE_H

