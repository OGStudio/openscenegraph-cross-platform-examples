FEATURE scene.h/Impl
void paintScene(osg::Node *scene)
{
    // Fragment shader to display everything in red colour.
    const char shaderFragment[] = R"(
        void main() {
          gl_FragColor = vec4(0.5, 0.3, 0.3, 1.0);
        }
    )";
    // Vertex shader to pass geometry vertices to fragment shader.
    const char shaderVertex[] = R"(
        void main() {
          gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        }
    )";
    auto prog = render::createShaderProgram(shaderVertex, shaderFragment);
    scene->getOrCreateStateSet()->setAttribute(prog);
}
