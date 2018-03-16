FEATURE rendering.h/Include
#include "resources.h"

FEATURE rendering.h/Impl
osg::ref_ptr<osg::Node> createScene(Resource &resource)
{
    // Load scene.
    auto scene = resourceNode(resource, "osgt");
    if (scene.valid())
    {
        // Load shaders.
        osg::Program *prog = createShaderProgram(shaderVertex, shaderFragment);
        // Apply shaders.
        scene->getOrCreateStateSet()->setAttribute(prog);
    }
    else
    {
        platformLog("Could not load scene");
    }
    return scene.release();
}
