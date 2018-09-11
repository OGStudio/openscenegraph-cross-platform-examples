FEATURE main.h/Include
#include "box.osgt.h"
#include "resource.h"
#include "scene.h"

#include <osg/MatrixTransform>

FEATURE main.h/Setup
this->setupBoxScene();

FEATURE main.h/Impl
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
            MAIN_EXAMPLE_LOG("ERROR Could not load scene");
        }
    }
