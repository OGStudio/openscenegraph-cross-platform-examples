FEATURE render.h/Include
#include <osg/Program>

FEATURE render.h/Impl
osg::Program *createShaderProgram(
    const std::string &vertexShader,
    const std::string &fragmentShader
) {
    // Load shaders.
    osg::Shader *vs = new osg::Shader(osg::Shader::VERTEX, vertexShader);
    osg::Shader *fs = new osg::Shader(osg::Shader::FRAGMENT, fragmentShader);
    // Compile shaders and compose shader program.
    osg::ref_ptr<osg::Program> prog = new osg::Program;
    prog->addShader(vs);
    prog->addShader(fs);
    return prog.release();
}
