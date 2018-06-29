FEATURE Example.h/Include
#include "box.osgt.h"
#include "resource.h"

FEATURE Example.h/Setup
this->setupBoxScene();

FEATURE Example.h/Impl
private:
    osg::ref_ptr<osg::MatrixTransform> scene;

    void setupBoxScene()
    {
        resource::Resource box("models", "box.osgt", box_osgt, box_osgt_len);
        auto node = resource::node(box);
        // Use MatrixTransform to allow box transformations.
        if (node)
        {
            this->scene = new osg::MatrixTransform;
            this->scene->addChild(node);
        }
        if (this->scene.valid())
        {
            this->app->setScene(scene);
        }
        else
        {
            OSGCPE_EXAMPLE_LOG("ERROR Could not load scene");
        }
    }
