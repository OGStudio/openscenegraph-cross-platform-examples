
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
// Application+handleEvent-web Start
#include <SDL2/SDL.h>

// Application+handleEvent-web End
// Application+setupWindow-web Start
#include <SDL2/SDL.h>

// Application+setupWindow-web End

// Application+CameraManipulator Start
#include <osgGA/TrackballManipulator>

// Application+CameraManipulator End
// Application+Debugging Start
#include "debug.h"

// Application+Debugging End
// Application+DebugCamera Start
#include "scene.h"

// Application+DebugCamera End
// Application+HTTPClient Start
#include "network.h"

// Application+HTTPClient End
// Application+Logging Start
#include "log.h"

// Application+Logging End
// Application+Rendering Start
#include "render.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

// Application+Rendering End

// MAIN_APPLICATION_LOG Start
#include "log.h"
#include "format.h"
#define MAIN_APPLICATION_LOG_PREFIX "main::Application(%p) %s"
#define MAIN_APPLICATION_LOG(...) \
    log::logprintf( \
        MAIN_APPLICATION_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
// MAIN_APPLICATION_LOG End

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
            // Application+CameraManipulator Start
            this->setupCameraManipulator();
            
            // Application+CameraManipulator End
            // Application+HTTPClient Start
            this->setupHTTPClient();
            
            // Application+HTTPClient End
            // Application+HTTPClientProcessor Start
            this->setupHTTPClientProcessor();
            
            // Application+HTTPClientProcessor End
            // Application+Debugging Start
            this->setupDebugging(name);
            
            // Application+Debugging End
            // Application+DebugCamera Start
            this->setupDebugCamera();
            
            // Application+DebugCamera End
// Application Start
        }
        ~Application()
        {

// Application End
            // Application+Debugging Start
            this->tearDebuggingDown();
            
            // Application+Debugging End
            // Application+HTTPClientProcessor Start
            this->tearHTTPClientProcessorDown();
            
            // Application+HTTPClientProcessor End
            // Application+HTTPClient Start
            this->tearHTTPClientDown();
            
            // Application+HTTPClient End
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
    // Application+handleEvent-web Start
    private:
        bool fingerEventsDetected = false;
    public:
        bool handleEvent(const SDL_Event &e)
        {
            // Get event queue.
            osgViewer::GraphicsWindow *gw =
                dynamic_cast<osgViewer::GraphicsWindow *>(
                    this->viewer->getCamera()->getGraphicsContext());
            if (!gw)
            {
                return false;
            }
            osgGA::EventQueue &queue = *(gw->getEventQueue());
    
            // Detect finger events.
            if (
                e.type == SDL_FINGERMOTION ||
                e.type == SDL_FINGERDOWN ||
                e.type == SDL_FINGERUP
            ) {
                this->fingerEventsDetected = true;
            }
            // Handle mouse events unless finger events are detected.
            if (!this->fingerEventsDetected)
            {
                return this->handleMouseEvent(e, queue);
            }
            // Handle finger events.
            return this->handleFingerEvent(e, queue);
        }
    
    private:
        bool handleFingerEvent(const SDL_Event &e, osgGA::EventQueue &queue)
        {
            int absX = this->windowWidth * e.tfinger.x;
            int absY = this->windowHeight * e.tfinger.y;
            auto correctedY = -(this->windowHeight - absY);
            switch (e.type)
            {
                case SDL_FINGERMOTION:
                    queue.mouseMotion(absX, correctedY);
                    return true;
                case SDL_FINGERDOWN: 
                    queue.mouseButtonPress(absX, correctedY, e.tfinger.fingerId);
                    return true;
                case SDL_FINGERUP:
                    queue.mouseButtonRelease(absX, correctedY, e.tfinger.fingerId);
                    return true;
                default:
                    break;
            }
            return false;
        }
    
        bool handleMouseEvent(const SDL_Event &e, osgGA::EventQueue &queue)
        {
            switch (e.type)
            {
                case SDL_MOUSEMOTION: {
                    auto correctedY = -(this->windowHeight - e.motion.y);
                    queue.mouseMotion(e.motion.x, correctedY);
                    return true;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    auto correctedY = -(this->windowHeight - e.button.y);
                    queue.mouseButtonPress(e.button.x, correctedY, e.button.button);
                    return true;
                }
                case SDL_MOUSEBUTTONUP: {
                    auto correctedY = -(this->windowHeight - e.button.y);
                    queue.mouseButtonRelease(e.button.x, correctedY, e.button.button);
                    return true;
                }
                default:
                    break;
            }
            return false;
        }
    // Application+handleEvent-web End
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
    // Application+setupWindow-web Start
    private:
        SDL_Window *sdlWindow = 0;
    public:
        bool setupWindow(
            const std::string &title,
            int width,
            int height
        ) {
            this->configureSDLGLContext();
            this->sdlWindow =
                SDL_CreateWindow(
                    title.c_str(),
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    width,
                    height,
                    SDL_WINDOW_OPENGL
                );
            if (!this->sdlWindow)
            {
                MAIN_APPLICATION_LOG(
                    "ERROR Could not create SDL window: '%s'\n",
                    SDL_GetError()
                );
                return false;
            }
    
            SDL_GL_CreateContext(this->sdlWindow);
            this->setupWindow(width, height);
    
            return true;
        }
        void configureSDLGLContext()
        {
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        }
    // Application+setupWindow-web End

    // Application+HTTPClient Start
    public:
        network::HTTPClient *httpClient;
    private:
        void setupHTTPClient()
        {
            this->httpClient = new network::HTTPClient;
        }
        void tearHTTPClientDown()
        {
            delete this->httpClient;
        }
    // Application+HTTPClient End
    // Application+HTTPClientProcessor Start
    public:
        network::HTTPClientProcessor *httpClientProcessor;
    private:
        const std::string httpClientProcessorCallbackName = "HTTPClientProcessor";
    
        void setupHTTPClientProcessor()
        {
            this->httpClientProcessor = new network::HTTPClientProcessor(this->httpClient);
            // Subscribe processor to be processed each frame.
            this->frameReporter.addCallback(
                [&] {
                    this->httpClientProcessor->process();
                },
                this->httpClientProcessorCallbackName
            );
        }
        void tearHTTPClientProcessorDown()
        {
            this->frameReporter.removeCallback(this->httpClientProcessorCallbackName);
            delete this->httpClientProcessor;
        }
    // Application+HTTPClientProcessor End
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
    // Application+CameraManipulator Start
    private:
        osg::ref_ptr<osgGA::TrackballManipulator> cameraManipulator;
        void setupCameraManipulator()
        {
            // Create manipulator: CRITICAL for mobile and web.
            this->cameraManipulator = new osgGA::TrackballManipulator;
            this->viewer->setCameraManipulator(this->cameraManipulator);
        }
    // Application+CameraManipulator End
    // Application+Debugging Start
    public:
        debug::Debugger *debugger;
    private:
        const std::string debuggerCallbackName = "Debugger";
    
        void setupDebugging(const std::string &name)
        {
            this->debugger = new debug::Debugger(this->httpClient, name);
            this->debugger->setBrokerURL("https://osgcpe-debug-broker.herokuapp.com");
    
            // Subscribe debugger to be processed each frame.
            this->frameReporter.addCallback(
                [&] {
                    this->debugger->process();
                },
                this->debuggerCallbackName
            );
        }
        void tearDebuggingDown()
        {
            // Unsubscribe debugger.
            this->frameReporter.removeCallback(this->debuggerCallbackName);
            delete this->debugger;
        }
    // Application+Debugging End
    // Application+DebugCamera Start
    private:
        debug::Page debugPage;
    public:
        void setupDebugCamera()
        {
            this->debugPage.title = "camera";
            this->setupDebugBGColor();
            this->setupDebugCameraOrientation();
            this->debugger->addPage(this->debugPage);
        }
    private:
        void setupDebugBGColor()
        {
            this->debugPage.addItem(
                "BGColor",
                // Getter.
                [&] {
                    auto color = this->camera()->getClearColor();
                    int r = color.r() * 255.0;
                    int g = color.g() * 255.0;
                    int b = color.b() * 255.0;
                    return format::printfString("%d,%d,%d", r, g, b);
                },
                // Setter.
                [&](const std::string &value) {
                    auto colorComponents = format::splitString(value, ",");
                    if (colorComponents.size() != 3)
                    {
                        OSGCPE_MAIN_APPLICATION_LOG("WARNING Skipping camera color application due to wrong value format");
                        OSGCPE_MAIN_APPLICATION_LOG("WARNING compoents number: '%d'", colorComponents.size());
                        return;
                    }
                    auto color = this->camera()->getClearColor();
                    color.r() = static_cast<float>(atoi(colorComponents[0].c_str())) / 255.0;
                    color.g() = static_cast<float>(atoi(colorComponents[1].c_str())) / 255.0;
                    color.b() = static_cast<float>(atoi(colorComponents[2].c_str())) / 255.0;
                    this->camera()->setClearColor(color);
                }
            );
        }
    
        void setupDebugCameraOrientation()
        {
            this->debugPage.addItem(
                "Position/Rotation",
                // Getter.
                [&] {
                    osg::Vec3d pos;
                    osg::Quat q;
                    this->cameraManipulator->getTransformation(pos, q);
                    auto rot = scene::quaternionToDegrees(q);
                    return
                        format::printfString(
                            "%f,%f,%f/%f,%f,%f",
                            pos.x(), pos.y(), pos.z(),
                            rot.x(), rot.y(), rot.z()
                        );
                }
            );
        }
    // Application+DebugCamera End
// Application Start
};
// Application End

// Example+04 Start
const auto EXAMPLE_TITLE = "OSGCPE-04: Remote debugging";
// Example+04 End

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
// Example Start
    }
    ~Example()
    {

// Example End
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

