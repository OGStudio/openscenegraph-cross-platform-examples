FEATURE Example.h/Include
#include "box.osgt.h"
#include "resource.h"

FEATURE Example.h/Setup
this->setupBoxScene();

FEATURE Example.h/Impl
private:
    osg::ref_ptr<osg::Node> scene;

    void setupBoxScene()
    {
        resource::Resource box("models", "box.osgt", box_osgt, box_osgt_len);
        this->scene = resource::node(box);
        if (this->scene.valid())
        {
            this->app->setScene(scene);
        }
        else
        {
            OSGCPE_EXAMPLE_LOG("ERROR Could not load scene");
        }
    }
