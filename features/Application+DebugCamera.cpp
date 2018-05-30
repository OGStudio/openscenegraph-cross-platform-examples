FEATURE Application.h/Setup
this->setupDebugCamera();

FEATURE Application.h/Impl
private:
    osg::Camera *camera;
public:
    void setupDebugCamera()
    {
        this->camera = this->viewer->getCamera();
        this->debugPage.title = "camera";

        this->debugPage.addItem(
            "BGColor",
            // Getter.
            [&] {
                auto color = this->camera->getClearColor();
                int r = color.r() * 255.0;
                int g = color.g() * 255.0;
                int b = color.b() * 255.0;
                return format::printfString("%d,%d,%d", r, g, b);
            },
            // Setter.
            [&](const std::string &value) {
                auto colorComponents = format::splitString(value, ",");
                if (colorComponents.size() != 3)
                {
                    OSGCPE_APPLICATION_LOG("WARNING Skipping camera color application due to wrong value format");
                    return;
                }
                auto color = this->camera->getClearColor();
                color.r() = static_cast<float>(atoi(colorComponents[0].c_str())) / 255.0;
                color.g() = static_cast<float>(atoi(colorComponents[1].c_str())) / 255.0;
                color.b() = static_cast<float>(atoi(colorComponents[2].c_str())) / 255.0;
                this->camera->setClearColor(color);
            }
        );
    }
