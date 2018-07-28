FEATURE core.h/Impl
public:
    osg::Camera *camera()
    {
        return this->viewer->getCamera();
    }
