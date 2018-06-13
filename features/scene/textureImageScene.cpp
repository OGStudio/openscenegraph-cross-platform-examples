FEATURE scene.h/Include
#include "resource.h"

FEATURE scene.h/Impl
void textureImageScene(
    const resource::Resource &shaderFrag,
    const resource::Resource &shaderVert,
    const resource::Resource &textureImage,
    osg::Node *scene
) {
    // Create shader program.
    auto prog =
        render::createShaderProgram(
            resource::string(shaderVert),
            resource::string(shaderFrag)
        );
    // Apply the program.
    auto material = scene->getOrCreateStateSet();
    material->setAttribute(prog);
    // Set texture image.
    material->setTextureAttributeAndModes(0, resource::createTexture(textureImage));
    material->addUniform(new osg::Uniform("image", 0));
}
