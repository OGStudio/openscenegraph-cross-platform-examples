FEATURE scene.h/Include
#include "render.h"
#include "resource.h"

FEATURE scene.h/Impl
void textureImageScene(
    osg::Node *scene,
    const resource::Resource &shaderFrag,
    const resource::Resource &shaderVert,
    const resource::Resource &textureImage
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
