
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RENDERING_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RENDERING_H

// rendering+Camera Start
#include <osg/Camera>

// rendering+Camera End
// rendering+Shaders Start
#include <osg/Program>

// rendering+Shaders End
// rendering+Scene Start
#include "resources.h"

// rendering+Scene End
// rendering+Box Start
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>

// rendering+Box End

namespace osgcpe
{

// rendering+Camera Start
// Configure camera with common defaults.
void setupCamera(
    osg::Camera *cam,
    osg::GraphicsContext *gc,
    double fovy,
    int width,
    int height
) {
    // Provide GC.
    cam->setGraphicsContext(gc);
    // Viewport must have the same size.
    cam->setViewport(new osg::Viewport(0, 0, width, height));
    // Clear depth and color buffers each frame.
    cam->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // Aspect ratio.
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    // Configure projection.
    cam->setProjectionMatrixAsPerspective(fovy, aspect, 1, 1000);
}
// rendering+Camera End
// rendering+Desktop Start
// Create graphics context for Linux, macOS, Windows.
osg::GraphicsContext *createGraphicsContext(
    const std::string &title,
    int x,
    int y,
    int width,
    int height)
{
    // Traits is a struct to combine necessary parameters.
    osg::GraphicsContext::Traits *traits =
        new osg::GraphicsContext::Traits;
    // Geometry.
    traits->x = x;
    traits->y = y;
    traits->width = width;
    traits->height = height;
    // Title.
    traits->windowName = title;
    // Window borders.
    traits->windowDecoration = true;
    // Double buffer (simply put, it's a flicker fix).
    traits->doubleBuffer = true;
    // Create GC.
    return osg::GraphicsContext::createGraphicsContext(traits);
}
// rendering+Desktop End
// rendering+Shaders Start
// Fragment shader to display everything in red colour.
static const char shaderFragment[] =
    "void main() {                             \n"
    "  gl_FragColor = vec4(0.5, 0.3, 0.3, 1.0);\n"
    "}                                         \n";
// Geometry shader to pass geometry vertices to fragment shader.
static const char shaderVertex[] =
    "void main() {                                              \n"
    "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  \n"
    "}                                                          \n";

osg::Program *createShaderProgram(
    const std::string &vertexShader,
    const std::string &fragmentShader
) {
    // Load shaders.
    osg::Shader *vs = new osg::Shader(osg::Shader::VERTEX, vertexShader);
    osg::Shader *fs = new osg::Shader(osg::Shader::FRAGMENT, fragmentShader);
    // Compile shaders and compose shader program.
    osg::Program *prog = new osg::Program;
    prog->addShader(vs);
    prog->addShader(fs);
    return prog;
}
// rendering+Shaders End
// rendering+Scene Start
void paintScene(osg::Node *scene)
{
    // Load shaders.
    osg::Program *prog = createShaderProgram(shaderVertex, shaderFragment);
    // Apply shaders.
    scene->getOrCreateStateSet()->setAttribute(prog);
}
osg::ref_ptr<osg::Node> createScene(Resource &resource)
{
    // Load scene.
    auto scene = resourceNode(resource, "osgt");
    if (!scene.valid())
    {
        log::log("ERROR Could not load scene");
    }
    return scene.release();
}
// rendering+Scene End
// rendering+Box Start
osg::MatrixTransform *createShape(osg::Shape *shape) {
    auto *hints = new osg::TessellationHints;
    hints->setDetailRatio(0.5);
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->addDrawable(new osg::ShapeDrawable(shape, hints));
    osg::ref_ptr<osg::MatrixTransform> node = new osg::MatrixTransform;
    node->addChild(geode);
    return node.release();
}

osg::MatrixTransform *createBox(const osg::Vec3f &size)
{
    auto *box = new osg::Box(osg::Vec3f(0, 0, 0), size.x(), size.y(), size.z());
    return createShape(box);
}

osg::MatrixTransform *createBox(float width)
{
    return createBox(osg::Vec3f(width, width, width));
}

// rendering+Box End

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RENDERING_H

