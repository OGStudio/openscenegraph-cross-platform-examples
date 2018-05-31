
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

// Application+Logging Start
#include "Logger.h"

// Application+Logging End
// Application+Rendering Start
#include "render.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

// Application+Rendering End
// Application+CameraManipulator Start
#include <osgGA/TrackballManipulator>

// Application+CameraManipulator End
// Application+Debugging Start
#include "DebugPage.h"

// Application+Debugging End
// Application+DebugCamera Start
#include "scene.h"

// Application+DebugCamera End
// Application+frame+Reporting Start
#include "Reporter.h"

// Application+frame+Reporting End

// Application+OSGCPE_APPLICATION_LOG Start
#include "log.h"
#include "format.h"
#define OSGCPE_APPLICATION_LOG_PREFIX "osgcpe-Application(%p) %s"
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
            // Application+CameraManipulator Start
            this->setupCameraManipulator();
            
            // Application+CameraManipulator End
            // Application+DebugCamera Start
            this->setupDebugCamera();
            
            // Application+DebugCamera End
        }
        ~Application()
        {
            // Application+Rendering Start
            this->tearRenderingDown();
            
            // Application+Rendering End
            // Application+Logging Start
            this->tearLoggingDown();
            
            // Application+Logging End
        }

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

        // Application+Logging Start
        private:
            Logger *logger;
            void setupLogging(const std::string &appName)
            {
                // Create custom logger.
                this->logger = new Logger(appName);
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
            DebugPage debugPage;
        // Application+Debugging End
        // Application+DebugCamera Start
        private:
            osg::Camera *camera;
        public:
            void setupDebugCamera()
            {
                this->camera = this->viewer->getCamera();
                this->debugPage.title = "camera";
                this->setupDebugBGColor();
                this->setupDebugCameraOrientation();
            }
        private:
            void setupDebugBGColor()
            {
                this->debugPage.addItem(
                    "BGColor",
                    // Getter.
                    [&] {
                        auto color = this->camera->getClearColor();
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
                            OSGCPE_APPLICATION_LOG("WARNING Skipping camera color application due to wrong value format");
                            OSGCPE_APPLICATION_LOG("WARNING compoents number: '%d'", colorComponents.size());
                            return;
                        }
                        auto color = this->camera->getClearColor();
                        color.r() = static_cast<float>(atoi(colorComponents[0].c_str())) / 255.0;
                        color.g() = static_cast<float>(atoi(colorComponents[1].c_str())) / 255.0;
                        color.b() = static_cast<float>(atoi(colorComponents[2].c_str())) / 255.0;
                        this->camera->setClearColor(color);
                    }
                );
            }
        
            void setupDebugCameraOrientation()
            {
                // TODO Use camera manipulator.
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
};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H

