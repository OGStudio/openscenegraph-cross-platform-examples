FEATURE Application.h/Impl
public:
    void setBGColor(const osg::Vec3 &color)
    {
        auto cam = this->viewer->getCamera();
        cam->setClearColor({color.x, color.y, color.z, 1.0});
    }
