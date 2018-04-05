
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RENDER_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RENDER_H

// render+createGraphicsContext-ios Start
#include <osgViewer/api/IOS/GraphicsWindowIOS>

// render+createGraphicsContext-ios End
// render+createShaderProgram Start
#include <osg/Program>

// render+createShaderProgram End
// render+setupCamera Start
#include <osg/Camera>

// render+setupCamera End

namespace osgcpe
{
namespace render
{

// render+createGraphicsContext-ios Start
// Create graphics context for iOS.
osg::GraphicsContext *createGraphicsContext(
    int width,
    int height,
    float scale,
    UIView *parentView
) {
    // Traits is a struct to combine necessary parameters.
    osg::GraphicsContext::Traits *traits =
        new osg::GraphicsContext::Traits;
    // Geometry.
    traits->x = 0;
    traits->y = 0;
    traits->width = width * scale;
    traits->height = height * scale;
    // Double buffer (simply put, it's a flicker fix).
    traits->doubleBuffer = true;
    // Parent view.
    osg::ref_ptr<osgViewer::GraphicsWindowIOS::WindowData> dat =
        new osgViewer::GraphicsWindowIOS::WindowData(
            parentView,
            osgViewer::GraphicsWindowIOS::WindowData::IGNORE_ORIENTATION
        );
    dat->setViewContentScaleFactor(scale);
    traits->inheritedWindowData = dat;
    // Create GC.
    return osg::GraphicsContext::createGraphicsContext(traits);
}
// render+createGraphicsContext-ios End
// render+createShaderProgram Start
osg::Program *createShaderProgram(
    const std::string &vertexShader,
    const std::string &fragmentShader
) {
    // Load shaders.
    osg::Shader *vs = new osg::Shader(osg::Shader::VERTEX, vertexShader);
    osg::Shader *fs = new osg::Shader(osg::Shader::FRAGMENT, fragmentShader);
    // Compile shaders and compose shader program.
    osg::ref_ptr<osg::Program> prog = new osg::Program;
    prog->addShader(vs);
    prog->addShader(fs);
    return prog.release();
}
// render+createShaderProgram End
// render+setupCamera Start
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
// render+setupCamera End


} // namespace render
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RENDER_H

