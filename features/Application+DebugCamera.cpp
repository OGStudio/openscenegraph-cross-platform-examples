FEATURE Application.h/Include
#include "scene.h"

FEATURE Application.h/Setup
this->setupDebugCamera();

FEATURE Application.h/Impl
private:
    debug::Page debugPage;
    osg::Camera *camera;
public:
    void setupDebugCamera()
    {
        this->debugPage.title = "camera";
        this->debugger->addPage(this->debugPage);
        this->camera = this->viewer->getCamera();
        this->setupDebugBGColor();
        this->setupDebugCameraOrientation();
    }
private:
    void setupDebugBGColor()
    {
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
                    OSGCPE_APPLICATION_LOG("WARNING compoents number: '%d'", colorComponents.size());
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

    void setupDebugCameraOrientation()
    {
        this->debugPage.addItem(
            "Position/Rotation",
            // Getter.
            [&] {
                osg::Vec3d pos;
                osg::Quat q;
                this->cameraManipulator->getTransformation(pos, q);
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
