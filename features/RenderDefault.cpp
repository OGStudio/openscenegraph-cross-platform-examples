FEATURE main.h/Include
#include <osgGA/TrackballManipulator>

FEATURE main.h/Construct
// Use single thread: CRITICAL for mobile and web.
mViewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
// Create manipulator: CRITICAL for mobile and web.
mViewer->setCameraManipulator(new osgGA::TrackballManipulator);

FEATURE main.h/Impl
void frame()
{
    mViewer->frame();
}
