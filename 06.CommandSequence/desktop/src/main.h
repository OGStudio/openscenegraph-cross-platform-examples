
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

// OSGCPE_MAIN_APPLICATION_LOG Start
#include "log.h"
#include "format.h"
#define OSGCPE_MAIN_APPLICATION_LOG_PREFIX "main::Application(%p) %s"
#define OSGCPE_MAIN_APPLICATION_LOG(...) \
    log::logprintf( \
        OSGCPE_MAIN_APPLICATION_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
// OSGCPE_MAIN_APPLICATION_LOG End

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

// OSGCPE_MAIN_EXAMPLE_LOG Start
#include "log.h"
#include "format.h"
#define OSGCPE_MAIN_EXAMPLE_LOG_PREFIX "main::Example(%p) %s"
#define OSGCPE_MAIN_EXAMPLE_LOG(...) \
    log::logprintf( \
        OSGCPE_MAIN_EXAMPLE_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
// OSGCPE_MAIN_EXAMPLE_LOG End

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
    // Application+run Start
    public:
        void run()
        {
            while (!this->viewer->done())
            {
                this->frame();
            }
        }
    // Application+run End
    // Application+setupWindow-desktop Start
    public:
        void setupWindow(
            const std::string &title,
            int x,
            int y,
            int width,
            int height
        ) {
            osg::GraphicsContext *gc =
                render::createGraphicsContext(title, x, y, width, height);
            // Configure viewer's camera with FOVY and window size.
            osg::Camera *cam = this->viewer->getCamera();
            render::setupCamera(cam, gc, 30, width, height);
        }
    // Application+setupWindow-desktop End

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
const auto EXAMPLE_TITLE = "ex06: command sequence";
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
    // Example+SequenceTest Start
    private:
        const std::string sequenceTestCallbackName = "SequenceTest";
        core::Sequence sequence;
        void setupSequenceTest()
        {
            // Do nothing for an empty scene.
            if (!this->scene.valid())
            {
                return;
            }
    
            // Register actions.
            sequence.registerAction(
                "waitForBoxSelection",
                OSGCPE_CORE_SEQUENCE_CALLBACK(this->waitForBoxSelection())
            );
            sequence.registerAction(
                "printBoxSelection",
                OSGCPE_CORE_SEQUENCE_CALLBACK(this->printBoxSelection())
            );
    
            sequence.setActionSequence({
                "waitForBoxSelection",
                "printBoxSelection",
                /*
                "disableBoxSelection",
                "startLoading",
                "startBoxRotation",
                "waitForLoadingFinish",
                "stopBoxRotation",
                "depictLoadingResult",
                "enableBoxSelection",
                */
            });
    
            this->setSequenceTestBoxSelectionEnabled(true);
        }
        void tearSequenceTestDown()
        {
            this->setSequenceTestBoxSelectionEnabled(false);
            // TODO Terminate animations?
        }
        void setSequenceTestBoxSelectionEnabled(bool state)
        {
            if (state)
            {
                this->boxSelected.addCallback(
                    [&] {
                        this->testSequence();
                    },
                    this->sequenceTestCallbackName
                );
            }
            else
            {
                this->boxSelected.removeCallback(this->sequenceTestCallbackName);
            }
        }
        void testSequence()
        {
            OSGCPE_MAIN_EXAMPLE_LOG("TODO test sequence");
            /*
            sequence.registerAction(
                "disableBoxSelection",
                OSGCPE_SEQUENCE_CALLBACK(this->setBoxSelectionEnabled(false))
            );
            sequence.registerAction(
                "enableBoxSelection",
                OSGCPE_SEQUENCE_CALLBACK(this->setBoxSelectionEnabled(true))
            );
            sequence.registerAction(
                "startLoading",
                OSGCPE_SEQUENCE_CALLBACK(this->startLoading())
            );
            sequence.registerAction(
                "startBoxRotation",
                OSGCPE_SEQUENCE_CALLBACK(this->startBoxRotation())
            );
            */
            sequence.setEnabled(true);
            // TODO Finish registration of actions.
    
        }
        core::Reporter *waitForBoxSelection()
        {
            return &this->boxSelected;
        }
        core::Reporter *printBoxSelection()
        {
            OSGCPE_MAIN_EXAMPLE_LOG("printBoxSelection: box has been selected");
            return 0;
        }
    /*
            void setupMatching()
            {
                this->matchReport.setDebugName("match");
                this->matchSequence.setDebugName("match");
                this->missSequence.setDebugName("miss");
    
                // Colors for BG color animation in case of match.
                auto start = GAME_BG_COLOR_DEFAULT;
                auto target = GAME_BG_COLOR_MATCH;
                float duration = GAME_BG_ANIM_MATCH_DURATION;
    
                // Successful match sequence.
                this->matchSequence
                    .subscribe(&this->matchReport)
                    // If we have a match.
                    .call(MJIN_REPORT_TRUE(this->hasMatch()))
                    // Disable node picking.
                    .call(MJIN_REPORT_ONCE(this->setPickingEnabled(false)))
    
                    // Reset BG timer, subscribe to ticks, and animate BG color.
                    .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                    .subscribe(&this->tickReport)
                    .call(MJIN_REPORT_MANY(this->animateBG(start, target, duration)))
                    .unsubscribe(&this->tickReport)
    
                    // Animate removal of the first selected node.
                    .call(MJIN_REPORT_ONCE(this->setupRemoval()))
                    .subscribe(&this->tickReport)
                    .call(MJIN_REPORT_MANY(this->animateRemoval()))
                    .unsubscribe(&this->tickReport)
                    // Delete the node.
                    .call(MJIN_REPORT_ONCE(this->removeNode()))
    
                    // Animate removal of the second selected node.
                    .call(MJIN_REPORT_ONCE(this->setupRemoval()))
                    .subscribe(&this->tickReport)
                    .call(MJIN_REPORT_MANY(this->animateRemoval()))
                    .unsubscribe(&this->tickReport)
                    // Delete the node.
                    .call(MJIN_REPORT_ONCE(this->removeNode()))
    
                    // De-animate BG color back to its initial value.
                    .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                    .subscribe(&this->tickReport)
                    .call(MJIN_REPORT_MANY(this->animateBG(target, start, duration)))
                    .unsubscribe(&this->tickReport)
                    
                    // Enable node picking.
                    .call(MJIN_REPORT_ONCE(this->setPickingEnabled(true)))
    
                    // Exit if no items left.
                    .call(MJIN_REPORT_ONCE(this->exitIfNoItems()))
                    ;
    
                // Colors for BG color animation in case of miss.
                target = GAME_BG_COLOR_MISS;
                duration = GAME_BG_ANIM_MISS_DURATION;
    
                // Miss sequence.
                this->missSequence
                    .subscribe(&this->matchReport)
                    // If we have a miss.
                    .call(MJIN_REPORT_TRUE(!this->hasMatch()))
                    // Disable node picking.
                    .call(MJIN_REPORT_ONCE(this->setPickingEnabled(false)))
    
                    // Reset BG timer, subscribe to ticks, and animate BG color.
                    .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                    .subscribe(&this->tickReport)
                    .call(MJIN_REPORT_MANY(this->animateBG(start, target, duration)))
                    .unsubscribe(&this->tickReport)
                    // De-animate BG color back to its initial value.
                    .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                    .subscribe(&this->tickReport)
                    .call(MJIN_REPORT_MANY(this->animateBG(target, start, duration)))
                    .unsubscribe(&this->tickReport)
    
                    // Animate BG color once again.
                    .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                    .subscribe(&this->tickReport)
                    .call(MJIN_REPORT_MANY(this->animateBG(start, target, duration)))
                    .unsubscribe(&this->tickReport)
                    // De-animate BG color back once again.
                    .call(MJIN_REPORT_ONCE(this->resetBGTimer()))
                    .subscribe(&this->tickReport)
                    .call(MJIN_REPORT_MANY(this->animateBG(target, start, duration)))
                    .unsubscribe(&this->tickReport)
    
                    // Deselect all nodes.
                    .call(MJIN_REPORT_ONCE(this->deselectAllNodes()))
                    // Enable node picking.
                    .call(MJIN_REPORT_ONCE(this->setPickingEnabled(true)))
                    ;
            }
    */
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
// Example Start
};
// Example End

} // namespace main.
} // namespace osgcpe.

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_MAIN_H

