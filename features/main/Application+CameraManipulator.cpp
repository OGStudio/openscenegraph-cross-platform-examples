FEATURE main.h/Include
#include <osgGA/TrackballManipulator>

FEATURE main.h/Setup
this->setupCameraManipulator();

FEATURE main.h/Impl
private:
    osg::ref_ptr<osgGA::TrackballManipulator> cameraManip;
    void setupCameraManipulator()
    {
        // Create manipulator: CRITICAL for mobile and web.
        this->cameraManip = new osgGA::TrackballManipulator;
        this->viewer->setCameraManipulator(this->cameraManip);
    }
public:
    osgGA::TrackballManipulator *cameraManipulator()
    {
        return this->cameraManip;
    }
