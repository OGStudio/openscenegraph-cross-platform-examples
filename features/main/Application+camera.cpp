FEATURE main.h/Impl
public:
    osg::Camera *camera()
    {
        return this->viewer->getCamera();
    }
