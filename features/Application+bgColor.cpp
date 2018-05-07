FEATURE Application.h/Impl
public:
    osg::Vec3 bgColor() const
    {
        auto cam = this->viewer->getCamera();
        auto color = cam->getClearColor(); 
        return { color.x, color.y, color.z };
    }
