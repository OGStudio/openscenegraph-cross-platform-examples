
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

// MAIN_EXAMPLE_LOG Start
#include "log.h"
#include "format.h"
#define MAIN_EXAMPLE_LOG_PREFIX "main::Example(%p) %s"
#define MAIN_EXAMPLE_LOG(...) \
    log::logprintf( \
        MAIN_EXAMPLE_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
// MAIN_EXAMPLE_LOG End

// Example+StaticPluginOSG Start
#include <osgDB/Registry>

// Reference (statically) plugins to read `osgt` file.
USE_OSGPLUGIN(osg2)
USE_SERIALIZER_WRAPPER_LIBRARY(osg)
// Example+StaticPluginOSG End
// Example+StaticPluginPNG Start
#include <osgDB/Registry>

// Reference (statically) plugins to read `png` file.
// Apple platforms use ImageIO. All others use libpng.
#ifdef __APPLE__
    USE_OSGPLUGIN(imageio)
#else
    USE_OSGPLUGIN(png)
#endif
// Example+StaticPluginPNG End

namespace osgcpe
{
namespace main
{

// Application Start
class Application
{
    public:
        Application(const std::string &name)
        {

// Application End
            // Application+Logging Start
            this->setupLogging(name);
            
            // Application+Logging End
            // Application+Rendering Start
            this->setupRendering();
            
            // Application+Rendering End
            // Application+Mouse Start
            this->setupMouse();
            
            // Application+Mouse End
// Application Start
        }
        ~Application()
        {

// Application End
            // Application+Mouse Start
            this->tearMouseDown();
            
            // Application+Mouse End
            // Application+Rendering Start
            this->tearRenderingDown();
            
            // Application+Rendering End
            // Application+Logging Start
            this->tearLoggingDown();
            
            // Application+Logging End
// Application Start
        }

// Application End
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
    // Application+handleMousePress-android Start
    public:
        void handleMousePress(bool down, float x, float y)
        {
            auto queue = this->viewer->getEventQueue();
            float correctedY = (this->windowHeight - y);
            if (down)
            {
                queue->mouseButtonPress(x, correctedY, 1 /* LMB */);
            }
            else
            {
                queue->mouseButtonRelease(x, correctedY, 1 /* LMB */);
            }
        }
    // Application+handleMousePress-android End
    // Application+setupWindow-embedded Start
    private:
        int windowWidth;
        int windowHeight;
    public:
        void setupWindow(int width, int height)
        {
            this->viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
            this->windowWidth = width;
            this->windowHeight = height;
        }
    // Application+setupWindow-embedded End

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
            // Make sure we reset the scene upon setting the same scene again.
            this->viewer->setSceneData(0);
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
// Application Start
};
// Application End

// Example+06 Start
const auto EXAMPLE_TITLE = "OSGCPE-06: Command sequence";
// Example+06 End

// Example Start
struct Example
{
    Application *app;

    typedef std::map<std::string, std::string> Parameters;

    Example(const Parameters &parameters)
    {
        this->app = new Application(EXAMPLE_TITLE);

// Example End
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
        // Example+SequenceTest Start
        this->setupSequenceTest();
        
        // Example+SequenceTest End
// Example Start
    }
    ~Example()
    {

// Example End
        // Example+SequenceTest Start
        this->tearSequenceTestDown();
        
        // Example+SequenceTest End
        // Example+BoxSelection Start
        this->tearBoxSelectionDown();
        
        // Example+BoxSelection End
// Example Start
        delete this->app;
    }

// Example End
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
                MAIN_EXAMPLE_LOG("ERROR Could not load scene");
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
    // Example+SequenceTest Start
    private:
        core::Sequence sequence;
        const std::string boxRotationCallbackName = "BoxRotation";
        const float rotationStepDegrees = 5;
        core::Reporter loadingSimulated;
        const std::string loadingSimulationCallbackName = "LoadingSimulation";
    
        core::Reporter bgChanged;
        const std::string bgChangeCallbackName = "BGChange";
        const osg::Vec4 bgColorDefault = {0.192, 0.192, 0.388, 0};
        const osg::Vec4 bgColorDim = {0.192, 0.192, 0.192, 0};
        const float bgColorStepDiff = 0.0049;
    
        void setupSequenceTest()
        {
            // Do nothing for an empty scene.
            if (!this->scene.valid())
            {
                return;
            }
    
            this->sequence.setActions({
                "enableBoxSelection",
                "waitForBoxSelection",
                "disableBoxSelection",
                "dimBackground",
                "startBoxRotation",
                "simulateLoading",
                "stopBoxRotation",
                "lightBackground",
            });
    
            // Register actions.
            CORE_REGISTER_SEQUENCE_ACTION(
                this->sequence,
                "waitForBoxSelection",
                this->waitForBoxSelection()
            );
            CORE_REGISTER_SEQUENCE_ACTION(
                this->sequence,
                "enableBoxSelection",
                this->setBoxSelectionEnabled(true)
            );
            CORE_REGISTER_SEQUENCE_ACTION(
                this->sequence,
                "disableBoxSelection",
                this->setBoxSelectionEnabled(false)
            );
            CORE_REGISTER_SEQUENCE_ACTION(
                this->sequence,
                "startBoxRotation",
                this->setBoxRotationEnabled(true)
            );
            CORE_REGISTER_SEQUENCE_ACTION(
                this->sequence,
                "stopBoxRotation",
                this->setBoxRotationEnabled(false)
            );
            CORE_REGISTER_SEQUENCE_ACTION(
                this->sequence,
                "simulateLoading",
                this->simulateLoading()
            );
            CORE_REGISTER_SEQUENCE_ACTION(
                this->sequence,
                "dimBackground",
                this->changeBackground(true)
            );
            CORE_REGISTER_SEQUENCE_ACTION(
                this->sequence,
                "lightBackground",
                this->changeBackground(false)
            );
    
            // Enable sequence.
            this->sequence.setEnabled(true);
        }
        void tearSequenceTestDown()
        {
            this->sequence.setEnabled(false);
        }
    
        // Box selection.
        core::Reporter *setBoxSelectionEnabled(bool state)
        {
            if (state)
            {
                this->setupBoxSelection();
            }
            else
            {
                this->tearBoxSelectionDown();
            }
    
            return 0;
        }
        core::Reporter *waitForBoxSelection()
        {
            return &this->boxSelected;
        }
    
        // Box rotation.
        void rotateBox()
        {
            auto rot = scene::simpleRotation(this->scene);
            rot.z() += this->rotationStepDegrees;
            scene::setSimpleRotation(this->scene, rot);
        }
        core::Reporter *setBoxRotationEnabled(bool state)
        {
            // Subscribe to `frameReporter`.
            if (state)
            {
                this->app->frameReporter.addCallback(
                    [&] {
                        this->rotateBox();
                    },
                    this->boxRotationCallbackName
                );
            }
            // Unsubscribe from `frameReporter`.
            else
            {
                this->app->frameReporter.removeCallback(
                    this->boxRotationCallbackName
                );
            }
    
            return 0;
        }
    
        // Loading simulation.
        core::Reporter *simulateLoading()
        {
            // Simulate loading for 2 seconds.
            int duration = 2;
            auto startDt = time(0);
    
            this->app->frameReporter.addCallback(
                [=] {
                    auto nowDt = time(0);
                    auto elapsed = nowDt - startDt;
                    if (elapsed >= duration)
                    {
                        this->app->frameReporter.removeCallback(this->loadingSimulationCallbackName);
                        this->loadingSimulated.report();
                    }
                },
                this->loadingSimulationCallbackName
            );
    
            return &this->loadingSimulated;
        }
    
        // Background.
        core::Reporter *changeBackground(bool dim)
        {
            auto targetColor = 
                dim ?
                this->bgColorDim :
                this->bgColorDefault
                ;
            auto targetColorDiff =
                dim ?
                -this->bgColorStepDiff :
                this->bgColorStepDiff
                ;
            this->app->frameReporter.addCallback(
                [=] {
                    // Change color.
                    auto color = this->app->camera()->getClearColor();
                    color.z() += targetColorDiff;
                    this->app->camera()->setClearColor(color);
    
                    // Find out if we're done.
                    auto targetColorHasBeenReached =
                        abs(color.z() - targetColor.z()) < 0.01;
                    if (targetColorHasBeenReached)
                    {
                        this->app->frameReporter.removeCallback(this->bgChangeCallbackName);
                        this->app->camera()->setClearColor(targetColor);
                        this->bgChanged.report();
                    }
                },
                this->bgChangeCallbackName
            );
    
            return &this->bgChanged;
        }
    // Example+SequenceTest End
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
            render::VBOSetupVisitor vbo;
            this->scene->accept(vbo);
        }
    // Example+VBO End
// Example Start
};
// Example End

} // namespace main.
} // namespace osgcpe.

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_MAIN_H

