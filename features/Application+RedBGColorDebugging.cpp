FEATURE Application.h/Setup
this->setupRedBGColorDebugging();

FEATURE Application.h/Impl
private:
    void setupRedBGColorDebugging()
    {
        this->debugPage.addItem(
            "RedBGColor",
            [&] {
                auto cam = this->viewer->getCamera();
                auto color = cam->getClearColor();
                int value = color.r() * 255.0;
                return log::printfString("%d", value);
            },
            [&](const std::string &value) {
                auto cam = this->viewer->getCamera();
                auto color = cam->getClearColor();
                color.r() = static_cast<float>(atoi(value.c_str())) / 255.0;
                cam->setClearColor(color);
            }
        );
    }

