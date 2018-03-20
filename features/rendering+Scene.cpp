FEATURE rendering.h/Include
#include "resources.h"

FEATURE rendering.h/Impl
void paintScene(osg::Node *scene)
{
    // Load shaders.
    osg::Program *prog = createShaderProgram(shaderVertex, shaderFragment);
    // Apply shaders.
    scene->getOrCreateStateSet()->setAttribute(prog);
}
osg::ref_ptr<osg::Node> createScene(Resource &resource)
{
    // Load scene.
    auto scene = resourceNode(resource, "osgt");
    if (!scene.valid())
    {
        log::log("ERROR Could not load scene");
    }
    return scene.release();
}
