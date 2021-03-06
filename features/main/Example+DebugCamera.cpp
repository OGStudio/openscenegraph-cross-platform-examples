FEATURE main.h/Include
#include "scene.h"

FEATURE main.h/Setup
this->setupDebugCamera();

FEATURE main.h/Impl
private:
    debug::Page debugPage;
public:
    void setupDebugCamera()
    {
        this->debugPage.title = "camera";
        this->setupDebugBGColor();
        this->setupDebugCameraOrientation();
        this->app->debugger->addPage(this->debugPage);
    }
private:
    void setupDebugBGColor()
    {
        this->debugPage.addItem(
            "BGColor",
            // Getter.
            [&] {
                auto color = this->app->camera()->getClearColor();
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
                    MAIN_APPLICATION_LOG(
                        "WARNING Skipping camera color application due to "
                        "wrong value format. Components number: '%d'",
                        colorComponents.size()
                    );
                    return;
                }
                auto color = this->app->camera()->getClearColor();
                color.r() = static_cast<float>(atoi(colorComponents[0].c_str())) / 255.0;
                color.g() = static_cast<float>(atoi(colorComponents[1].c_str())) / 255.0;
                color.b() = static_cast<float>(atoi(colorComponents[2].c_str())) / 255.0;
                this->app->camera()->setClearColor(color);
            }
        );
    }

    void setupDebugCameraOrientation()
    {
        this->debugPage.addItem(
            "Position/Rotation",
            // Getter.
            [&] {
                osg::Vec3d pos;
                osg::Quat q;
                this->app->cameraManipulator()->getTransformation(pos, q);
                auto rot = scene::quaternionToDegrees(q);
                return
                    format::printfString(
                        "%f,%f,%f/%f,%f,%f",
                        pos.x(), pos.y(), pos.z(),
                        rot.x(), rot.y(), rot.z()
                    );
            }
        );
    }
