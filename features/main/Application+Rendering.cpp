FEATURE main.h/Include
#include "render.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

FEATURE main.h/Setup
this->setupRendering();

FEATURE main.h/TearDown
this->tearRenderingDown();

FEATURE main.h/Impl
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
