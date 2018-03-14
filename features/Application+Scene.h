FEATURE Application.h/Include
#include "rendering.h"
#include "Resource.h"
#include "resources.h"

FEATURE Application.h/Impl
public:
    void loadScene(Resource &resource)
    {
        // Load scene.
        osg::Node *scene = resourceNode(resource, "osgt");
        if (!scene)
        {
            platformLog("Could not load scene");
            return;
        }
        platformLog("Scene has been loaded");
        // TODO FEATURE VBO/IMPL
        // Load shaders.
        osg::Program *prog = createShaderProgram(shaderVertex, shaderFragment);
        // Apply shaders.
        scene->getOrCreateStateSet()->setAttribute(prog);
        // Set scene.
        this->viewer->setSceneData(scene);
    }
