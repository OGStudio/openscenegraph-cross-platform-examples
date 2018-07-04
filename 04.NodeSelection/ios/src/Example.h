
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H
        
#include "Application.h"
#include "scene.h"
// Example+VBO Start
#include "render.h"

// Example+VBO End
// Example+BoxScene Start
#include "box.osgt.h"
#include "resource.h"

#include <osg/MatrixTransform>

// Example+BoxScene End
// Example+TextureImageScene Start
#include "resource.h"
#include "ppl.frag.h"
#include "ppl.vert.h"
#include "digit.png.h"

// Example+TextureImageScene End

// Example+OSGCPE_EXAMPLE_LOG Start
#include "log.h"
#include "format.h"
#define OSGCPE_EXAMPLE_LOG_PREFIX "osgcpe::Example(%p) %s"
#define OSGCPE_EXAMPLE_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_EXAMPLE_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )

// Example+OSGCPE_EXAMPLE_LOG End
// Example+StaticPluginOSG Start
// Reference (statically) plugins to read `osgt` file.
USE_OSGPLUGIN(osg2)
USE_SERIALIZER_WRAPPER_LIBRARY(osg)
// Example+StaticPluginOSG End
// Example+StaticPluginImageIO Start
// Reference (statically) plugins to read `png` file.
USE_OSGPLUGIN(imageio)
// Example+StaticPluginImageIO End

namespace osgcpe
{

// Example+04 Start
const auto EXAMPLE_TITLE = "Ex04";
// Example+04 End

struct Example
{

    osgcpe::Application *app;

    Example()
    {
        this->app = new osgcpe::Application(EXAMPLE_TITLE);

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
    }
    ~Example()
    {
        // Example+BoxRotation Start
        this->tearBoxRotationDown();
        
        // Example+BoxRotation End
        // Example+BoxSelection Start
        this->tearBoxSelectionDown();
        
        // Example+BoxSelection End

        delete this->app;
    }

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
                OSGCPE_EXAMPLE_LOG("ERROR Could not load scene");
            }
        }
    // Example+BoxScene End
    // Example+BoxSelection Start
    private:
        Reporter boxSelected;
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

};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_EXAMPLE_H

