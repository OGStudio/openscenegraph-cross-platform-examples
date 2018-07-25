
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

