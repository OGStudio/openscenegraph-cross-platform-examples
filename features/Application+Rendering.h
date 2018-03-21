FEATURE Application.h/Include
#include "render.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

FEATURE Application.h/Setup
this->setupRendering();

FEATURE Application.h/TearDown
this->tearRenderingDown();

FEATURE Application.h/Impl
public:
    void frame()
    {
        this->viewer->frame();
    }
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
