
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
#include "rendering.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

// Application+Rendering End
// Application+Scene Start
#include "rendering.h"
#include "Resource.h"
#include "resources.h"

// Application+Scene End


namespace osgcpe
{

class Application
{
    public:
        Application()
        {
            // Application+Logging Start
            this->setupLogging();
            
            // Application+Logging End
            // Application+Rendering Start
            this->setupRendering();
            
            // Application+Rendering End
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

        // Application+Logging Start
        private:
            Logger *logger;
            void setupLogging()
            {
                // Create custom logger.
                this->logger = new Logger;
                // Provide the logger to OpenSceneGraph.
                osg::setNotifyHandler(this->logger);
                // Only accept notifications of Info level or higher
                // like warnings and errors.
                osg::setNotifyLevel(osg::INFO);
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
            void frame()
            {
                this->viewer->frame();
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
        // Application+RenderingDesktop Start
        public:
            void run()
            {
                this->viewer->run();
            }
            void setupWindow(
                const std::string &title,
                int x,
                int y,
                int width,
                int height
            ) {
                osg::GraphicsContext *gc =
                    createGraphicsContext(title, x, y, width, height);
                // Configure viewer's camera with FOVY and window size.
                osg::Camera *cam = this->viewer->getCamera();
                setupCamera(cam, gc, 30, width, height);
            }
        
        // Application+RenderingDesktop End
        // Application+Scene Start
        public:
            void loadScene(Resource &resource)
            {
                // Load scene.
                osg::Node *scene = resourceNode(resource, "osgt");
                if (!scene)
                {
                    platformLog("Could not load scene");
                    return;
                }
                platformLog("Scene has been loaded");
                // TODO FEATURE VBO/IMPL
                // Load shaders.
                osg::Program *prog = createShaderProgram(shaderVertex, shaderFragment);
                // Apply shaders.
                scene->getOrCreateStateSet()->setAttribute(prog);
                // Set scene.
                this->viewer->setSceneData(scene);
            }
        // Application+Scene End
};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H

