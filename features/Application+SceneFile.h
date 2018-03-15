FEATURE Application.h/Include
#include "rendering.h"
#include <osgDB/ReadFile>

#include "InfoVisitor.h"

FEATURE Application.h/Impl
public:
    void loadScene(const std::string &fileName)
    {
        // Load scene.
        osg::Node *scene = osgDB::readNodeFile(fileName);
        if (!scene)
        {
            platformLog("Could not load scene");
            return;
        }
        platformLog("Scene has been loaded");
        InfoVisitor iv;
        scene->accept(iv);
        // TODO FEATURE VBO/IMPL
        // Load shaders.
        osg::Program *prog = createShaderProgram(shaderVertex, shaderFragment);
        // Apply shaders.
        scene->getOrCreateStateSet()->setAttribute(prog);
        // Set scene.
        this->viewer->setSceneData(scene);
    }
