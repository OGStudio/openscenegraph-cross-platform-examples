
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_MAIN_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_MAIN_H

// Application+frame+Reporting Start
#include "core.h"

// Application+frame+Reporting End

// Application+Logging Start
#include "log.h"

// Application+Logging End
// Application+Mouse Start
#include "input.h"

// Application+Mouse End
// Application+Rendering Start
#include "render.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

// Application+Rendering End


// Example+BoxScene Start
#include "box.osgt.h"
#include "resource.h"
#include "scene.h"

#include <osg/MatrixTransform>

// Example+BoxScene End
// Example+TextureImageScene Start
#include "resource.h"
#include "ppl.frag.h"
#include "ppl.vert.h"
#include "digit.png.h"

// Example+TextureImageScene End
// Example+VBO Start
#include "render.h"

// Example+VBO End


// Example+StaticPluginImageIO Start
// Reference (statically) plugins to read `png` file.
USE_OSGPLUGIN(imageio)
// Example+StaticPluginImageIO End
// Example+StaticPluginOSG Start
// Reference (statically) plugins to read `osgt` file.
USE_OSGPLUGIN(osg2)
USE_SERIALIZER_WRAPPER_LIBRARY(osg)
// Example+StaticPluginOSG End

namespace osgcpe
{
namespace main
{

            // Application+Logging Start
            this->setupLogging(name);
            
            // Application+Logging End
            // Application+Rendering Start
            this->setupRendering();
            
            // Application+Rendering End
            // Application+Mouse Start
            this->setupMouse();
            
            // Application+Mouse End
            // Application+Mouse Start
            this->tearMouseDown();
            
            // Application+Mouse End
            // Application+Rendering Start
            this->tearRenderingDown();
            
            // Application+Rendering End
            // Application+Logging Start
            this->tearLoggingDown();
            
            // Application+Logging End
    // Application+camera Start
    public:
        osg::Camera *camera()
        {
            return this->viewer->getCamera();
        }
    // Application+camera End
    // Application+frame+Reporting Start
    public:
        core::Reporter frameReporter;
        void frame()
        {
            this->viewer->frame();
            this->frameReporter.report();
        }
    // Application+frame+Reporting End
    // Application+setupWindow-ios Start
    UIView *setupWindow(
        int width,
        int height,
        float scale,
        UIView *parentView
    ) {
        osgViewer::GraphicsWindowIOS *gc =
            dynamic_cast<osgViewer::GraphicsWindowIOS *>(
                render::createGraphicsContext(width, height, scale, parentView)
            );
        // Configure viewer's camera with FOVY and window size.
        osg::Camera *cam = this->viewer->getCamera();
        render::setupCamera(cam, gc, 30, width * scale, height * scale);
        // Return UIView for embedding.
        return (UIView *)gc->getView();
    }
    // Application+setupWindow-ios End

    // Application+Logging Start
    private:
        log::Logger *logger;
        void setupLogging(const std::string &appName)
        {
            // Create custom logger.
            this->logger = new log::Logger(appName);
            // Provide the logger to OpenSceneGraph.
            osg::setNotifyHandler(this->logger);
            // Only accept notifications of Info level or higher
            // like warnings and errors.
            //osg::setNotifyLevel(osg::INFO);
            osg::setNotifyLevel(osg::WARN);
        }
        void tearLoggingDown()
        {
            // Remove the logger from OpenSceneGraph.
            // This also destroys the logger: no need to deallocate it manually.
            osg::setNotifyHandler(0);
        }
    // Application+Logging End
    // Application+Rendering Start
    public:
        void setScene(osg::Node *scene)
        {
            this->viewer->setSceneData(scene);
        }
    private:
        osgViewer::Viewer *viewer;
        void setupRendering()
        {
            // Create OpenSceneGraph viewer.
            this->viewer = new osgViewer::Viewer;
            // Use single thread: CRITICAL for mobile and web.
            this->viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
            // Create manipulator: CRITICAL for mobile and web.
            this->viewer->setCameraManipulator(new osgGA::TrackballManipulator);
        }
        void tearRenderingDown()
        {
            delete this->viewer;
        }
    // Application+Rendering End
    // Application+Mouse Start
    public:
        osg::ref_ptr<input::Mouse> mouse;
    private:
        void setupMouse()
        {
            // Create mouse events' handler.
            this->mouse = new input::Mouse;
            // Register it.
            this->viewer->addEventHandler(this->mouse);
        }
        void tearMouseDown()
        {
            // This also removes Mouse instance.
            this->viewer->removeEventHandler(this->mouse);
        }
    // Application+Mouse End

// Example+04 Start
const auto EXAMPLE_TITLE = "Ex04";
// Example+04 End

        // Example+BoxScene Start
        this->setupBoxScene();
        
        // Example+BoxScene End
        // Example+VBO Start
        this->setupSceneVBO();
        
        // Example+VBO End
        // Example+TextureImageScene Start
        this->setupSceneTexturing();
        
        // Example+TextureImageScene End
        // Example+BoxSelection Start
        this->setupBoxSelection();
        
        // Example+BoxSelection End
        // Example+BoxRotation Start
        this->setupBoxRotation();
        
        // Example+BoxRotation End
        // Example+BoxRotation Start
        this->tearBoxRotationDown();
        
        // Example+BoxRotation End
        // Example+BoxSelection Start
        this->tearBoxSelectionDown();
        
        // Example+BoxSelection End
    // Example+BoxRotation Start
    private:
        const std::string boxRotationCallbackName = "BoxRotation";
        void setupBoxRotation()
        {
            // Do nothing for an empty scene.
            if (!this->scene.valid())
            {
                return;
            }
    
            // Start box rotation upon box selection.
            this->boxSelected.addCallback(
                [&] {
                    this->rotateBox();
                },
                this->boxRotationCallbackName
            );
        }
        void tearBoxRotationDown()
        {
            this->boxSelected.removeCallback(this->boxRotationCallbackName);
            this->stopBoxRotationAnimation();
        }
        scene::LinearInterpolator interpolator;
        osg::Timer rotationTimer;
        void rotateBox()
        {
            // Get current box rotation along X.
            auto rot = scene::simpleRotation(this->scene);
            auto srcX = rot.x();
    
            // Configure interpolation.
            this->interpolator.keyValues = {
                {0, srcX},
                {0.5, srcX + 45}, // Rotate by 45 degrees in 0.5 seconds.
                {2, srcX}, // Rotate back in 2 - 0.5 = 1.5 seconds.
            };
    
            this->startBoxRotationAnimation();
        }
        void animateBoxRotation()
        {
            float elapsed = this->rotationTimer.time_s();
            auto lastKeyValue = this->interpolator.keyValues.back();
            float stopTime = lastKeyValue.key;
            // Stop animation.
            if (elapsed > stopTime)
            {
                this->setBoxRotationX(lastKeyValue.value);
                this->stopBoxRotationAnimation();
                return;
            }
            // Animate.
            auto value = this->interpolator.valueFor(elapsed);
            this->setBoxRotationX(value);
        }
        void setBoxRotationX(float x)
        {
            auto rot = scene::simpleRotation(this->scene);
            rot.x() = x;
            scene::setSimpleRotation(this->scene, rot);
        }
        void startBoxRotationAnimation()
        {
            // Reset timer.
            this->rotationTimer.setStartTick();
            // Subscribe to frame ticks.
            this->app->frameReporter.addCallback(
                [&] {
                    this->animateBoxRotation();
                },
                this->boxRotationCallbackName
            );
        }
        void stopBoxRotationAnimation()
        {
            // Unsubscribe from frame ticks.
            this->app->frameReporter.removeCallback(this->boxRotationCallbackName);
        }
    // Example+BoxRotation End
    // Example+BoxScene Start
    private:
        osg::ref_ptr<osg::MatrixTransform> scene;
    
        void setupBoxScene()
        {
            resource::Resource box("models", "box.osgt", box_osgt, box_osgt_len);
            auto node = resource::node(box);
            // Use MatrixTransform to allow box transformations.
            if (node)
            {
                this->scene = new osg::MatrixTransform;
                this->scene->addChild(node);
            }
            if (this->scene.valid())
            {
                this->app->setScene(scene);
            }
            else
            {
                OSGCPE_MAIN_EXAMPLE_LOG("ERROR Could not load scene");
            }
        }
    // Example+BoxScene End
    // Example+BoxSelection Start
    private:
        core::Reporter boxSelected;
        const std::string boxSelectionCallbackName = "BoxSelection";
        const unsigned int selectionNodeMask = 0x00000004;
        void setupBoxSelection()
        {
            // Make box node selectable by excluding specific node mask.
            this->scene->setNodeMask(
                this->scene->getNodeMask() & ~this->selectionNodeMask
            );
    
            // Listen to mouse clicks.
            this->app->mouse->pressedButtonsChanged.addCallback(
                [&] {
                    bool clicked = !this->app->mouse->pressedButtons.empty();
                    if (clicked)
                    {
                        this->tryToSelectBox();
                    }
                },
                this->boxSelectionCallbackName
            );
        }
        void tearBoxSelectionDown()
        {
            this->app->mouse->pressedButtonsChanged.removeCallback(
                this->boxSelectionCallbackName
            );
        }
        void tryToSelectBox()
        {
            auto node =
                scene::nodeAtPosition(
                    this->app->mouse->position,
                    this->app->camera(),
                    this->selectionNodeMask
                );
            if (node)
            {
                // Since we don't have other nodes in the scene,
                // we are sure it's the box.
                this->boxSelected.report();
            }
        }
    // Example+BoxSelection End
    // Example+TextureImageScene Start
    private:
        void setupSceneTexturing()
        {
            // Do nothing for an empty scene.
            if (!this->scene.valid())
            {
                return;
            }
            resource::Resource shaderFrag("shaders", "ppl.frag", ppl_frag, ppl_frag_len);
            resource::Resource shaderVert("shaders", "ppl.vert", ppl_vert, ppl_vert_len);
            resource::Resource texture("images", "digit.png", digit_png, digit_png_len);
            scene::textureImageScene(this->scene, shaderFrag, shaderVert, texture);
        }
    // Example+TextureImageScene End
    // Example+VBO Start
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
    // Example+VBO End

} // namespace main.
} // namespace osgcpe.

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_MAIN_H

