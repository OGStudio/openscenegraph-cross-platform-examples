
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
// Example+ScriptingTest Start
#include "script.h"

#include <sol.hpp>

// Example+ScriptingTest End
// Example+TextureImageScene Start
#include "resource.h"
#include "ppl.frag.h"
#include "ppl.vert.h"
#include "digit.png.h"

// Example+TextureImageScene End

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

// Example+07 Start
const auto EXAMPLE_TITLE = "OSGCPE-07: Lua scripting";
// Example+07 End

// Example Start
struct Example
{
    Application *app;

    typedef std::map<std::string, std::string> Parameters;

    Example(const Parameters &parameters)
    {
        this->app = new Application(EXAMPLE_TITLE);

// Example End
        // Example+Parameters Start
        this->setupParameters(parameters);
        
        // Example+Parameters End
        // Example+BoxScene Start
        this->setupBoxScene();
        
        // Example+BoxScene End
        // Example+TextureImageScene Start
        this->setupSceneTexturing();
        
        // Example+TextureImageScene End
        // Example+ScriptingTest Start
        this->setupScriptingTest();
        
        // Example+ScriptingTest End
// Example Start
    }
    ~Example()
    {

// Example End
        // Example+ScriptingTest Start
        this->tearScriptingTestDown();
        
        // Example+ScriptingTest End
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
    // Example+Parameters Start
    private:
        Parameters parameters;
        void setupParameters(const Parameters &parameters)
        {
            this->parameters = parameters;
        }
    // Example+Parameters End
    // Example+ScriptingTest Start
    private:
        script::Environment *environment;
        void setupScriptingTest()
        {
            this->environment = new script::Environment;
            this->setupSampleClient();
    
            // Call sample client through Environment interface.
            auto values = this->environment->call("sample", {"A", "B", "C"});
            for (auto value : values)
            {
                MAIN_EXAMPLE_LOG("sample. value: '%s'", value.c_str());
            }
    
            this->setupLuaEnvironment();
            this->loadCLIScript();
    
            // Call Lua side client.
            MAIN_EXAMPLE_LOG("Calling Lua client");
            this->environment->call("lua", {"abc"});
            for (auto value : values)
            {
                MAIN_EXAMPLE_LOG("lua. value: '%s'", value.c_str());
            }
    
            this->setupMouseTransmitter();
        }
        void tearScriptingTestDown()
        {
            this->tearMouseTransmitterDown();
            this->tearLuaEnvironmentDown();
            delete this->environment;
            this->tearSampleClientDown();
        }
    
        // Sample client.
    
        script::EnvironmentClient *sampleClient;
    
        void setupSampleClient()
        {
            this->sampleClient = new script::EnvironmentClient;
            this->environment->addClient(this->sampleClient);
            this->sampleClient->respondsToKey =
                SCRIPT_ENVIRONMENT_CLIENT_RESPONDS_TO_KEY(
                    return (key == "sample");
                );
            this->sampleClient->call =
                SCRIPT_ENVIRONMENT_CLIENT_CALL(
                    MAIN_EXAMPLE_LOG("sample.call(%s)", key.c_str());
                    return values;
                );
        }
        void tearSampleClientDown()
        {
            delete this->sampleClient;
        }
    
        // Lua environment.
     
        sol::state *lua;
    
        void setupLuaEnvironment()
        {
            this->lua = new sol::state;
            this->lua->open_libraries();
            // Register Environment instance.
            (*this->lua)["ENV"] = this->environment;
            // Register Environment class.
            this->lua->new_usertype<script::Environment>(
                "Environment",
                // 'addClient' method.
                "addClient",
                &script::Environment::addClient,
                // 'call' method.
                "call",
                [](script::Environment &env, const std::string &key, sol::nested<script::EnvironmentClient::Values> values)
                {
                    return env.call(key, values);
                }
            );
            // Register EnvironmentClient class.
            this->lua->new_usertype<script::EnvironmentClient>(
                "EnvironmentClient",
                // 'call' method.
                "call",
                sol::property(
                    [](script::EnvironmentClient &ec, sol::function luaCallback)
                    {
                        ec.call =
                            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                                sol::nested<script::EnvironmentClient::Values> result = luaCallback(key, sol::as_table(values));
                                return std::move(result.source);
                            );
                    }
                ),
                // 'respondsToKey' method.
                "respondsToKey",
                &script::EnvironmentClient::respondsToKey
            );
        }
        void tearLuaEnvironmentDown()
        {
            delete this->lua;
        }
        void loadCLIScript()
        {
            // Make sure `script` parameter exists.
            auto it = this->parameters.find("script");
            if (it == this->parameters.end())
            {
                return;
            }
    
            auto path = it->second;
            MAIN_EXAMPLE_LOG("Loading script '%s'", path.c_str());
            std::ifstream localScript(path);
            if (localScript)
            {
                // Read file contents into string.
                std::string fileContents(
                    (std::istreambuf_iterator<char>(localScript)),
                    (std::istreambuf_iterator<char>())
                );
                // Execute the script.
                this->lua->script(fileContents);
                MAIN_EXAMPLE_LOG("Successfully loaded local script");
            }
            else
            {
                MAIN_EXAMPLE_LOG("ERROR Could not read local script");
            }
        }
    
        // Mouse transmitter.
        const std::string mouseCallbackName = "MouseTransmitter";
    
        void setupMouseTransmitter()
        {
            this->app->mouse->pressedButtonsChanged.addCallback(
                [=] {
                    this->transmitMouseButtons();
                },
                this->mouseCallbackName
            );
        }
        void tearMouseTransmitterDown()
        {
            this->app->mouse->pressedButtonsChanged.removeCallback(
                this->mouseCallbackName
            );
        }
        void transmitMouseButtons()
        {
            /*
            // Convert buttons to string representation.
            auto buttons = this->app->mouse->pressedButtons;
            std::vector<std::string> strbuttons;
            for (auto button : buttons)
            {
                strbuttons.push_back(mouseButtonToString(button));
            }
            */
            // Transmit.
            //auto key = "application.mouse.pressedButtons";
            auto key = "app";
            this->environment->call(key, {"app"});
        }
    // Example+ScriptingTest End
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

