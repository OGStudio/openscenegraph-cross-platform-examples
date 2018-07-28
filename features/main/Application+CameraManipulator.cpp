FEATURE main.h/Include
#include <osgGA/TrackballManipulator>

FEATURE main.h/Setup
this->setupCameraManipulator();

FEATURE main.h/Impl
private:
    osg::ref_ptr<osgGA::TrackballManipulator> cameraManipulator;
    void setupCameraManipulator()
    {
        // Create manipulator: CRITICAL for mobile and web.
        this->cameraManipulator = new osgGA::TrackballManipulator;
        this->viewer->setCameraManipulator(this->cameraManipulator);
    }
