
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H

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
// Application+frame+Reporting Start
#include "Reporter.h"

// Application+frame+Reporting End
// Application+handleEvent-web Start
#include <SDL2/SDL.h>

// Application+handleEvent-web End

// Application+OSGCPE_APPLICATION_LOG Start
#include "log.h"
#include "format.h"
#define OSGCPE_APPLICATION_LOG_PREFIX "osgcpe::Application(%p) %s"
#define OSGCPE_APPLICATION_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_APPLICATION_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )

// Application+OSGCPE_APPLICATION_LOG End

namespace osgcpe
{

class Application
{
    public:
        Application(const std::string &name)
        {
            // Application+Logging Start
            this->setupLogging(name);
            
            // Application+Logging End
            // Application+Rendering Start
            this->setupRendering();
            
            // Application+Rendering End
            // Application+HTTPClient Start
            this->setupHTTPClient();
            
            // Application+HTTPClient End
        }
        ~Application()
        {
            // Application+HTTPClient Start
            this->tearHTTPClientDown();
            
            // Application+HTTPClient End
            // Application+Rendering Start
            this->tearRenderingDown();
            
            // Application+Rendering End
            // Application+Logging Start
            this->tearLoggingDown();
            
            // Application+Logging End
        }

        // Application+camera Start
        public:
            osg::Camera *camera()
            {
                return this->viewer->getCamera();
            }
        // Application+camera End
        // Application+frame+Reporting Start
        public:
            Reporter frameReporter;
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
                    fingerEventsDetected = true;
                }
                // Handle mouse events unless finger events are detected.
                if (!fingerEventsDetected)
                {
                    return handleMouseEvent(e, queue);
                }
                // Handle finger events.
                return handleFingerEvent(e, queue);
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

        // Application+HTTPClient Start
        public:
            network::HTTPClient *httpClient;
        private:
            const std::string httpClientCallbackName = "HTTPClient";
        
            void setupHTTPClient()
            {
                this->httpClient = new network::HTTPClient;
        
                // Subscribe HTTP client to be processed each frame.
                this->frameReporter.addCallback(
                    [&] {
                        if (this->httpClient->needsProcessing())
                        {
                            this->httpClient->process();
                        }
                    },
                    this->httpClientCallbackName
                );
            }
            void tearHTTPClientDown()
            {
                // Unsubscribe HTTP client.
                this->frameReporter.removeCallback(this->httpClientCallbackName);
                delete this->httpClient;
            }
        // Application+HTTPClient End
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
};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H

