FEATURE scene.h/Include
#include "resources.h"

FEATURE scene.h/Impl
void textureImageScene(
    const Resource &shaderFrag,
    const Resource &shaderVert,
    const Resource &textureImage,
    osg::Node *scene
) {
    // Create shader program.
    auto prog =
        render::createShaderProgram(
            resources::string(shaderVert),
            resources::string(shaderFrag)
        );
    // Apply the program.
    auto material = scene->getOrCreateStateSet();
    material->setAttribute(prog);
    // Set texture image.
    material->setTextureAttributeAndModes(0, resources::createTexture(textureImage));
    material->addUniform(new osg::Uniform("image", 0));
}
