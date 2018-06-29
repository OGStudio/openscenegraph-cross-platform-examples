FEATURE Example.h/Include
#include "resource.h"
#include "ppl.frag.h"
#include "ppl.vert.h"
#include "digit.png.h"

FEATURE Example.h/Setup
this->setupSceneTexturing();

FEATURE Example.h/Impl
private:
    void setupSceneTexturing()
    {
        // Do nothing for an empty scene.
        if (!this->scene.valid())
        {
            return;
        }
        resource::Resource shaderFrag("shaders", "ppl.frag", ppl_frag, ppl_frag_len);
        resource::Resource shaderVert("shaders", "ppl.vert", ppl_vert, ppl_vert_len);
        resource::Resource texture("images", "digit.png", digit_png, digit_png_len);
        scene::textureImageScene(this->scene, shaderFrag, shaderVert, texture);
    }
