FEATURE Example.h/Include
#include "resource.h"
#include "ppl.frag.h"
#include "ppl.vert.h"
#include "digit.png.h"

FEATURE Example.h/Impl
osgcpe::resource::Resource shaderFrag("shaders", "ppl.frag", ppl_frag, ppl_frag_len);
osgcpe::resource::Resource shaderVert("shaders", "ppl.vert", ppl_vert, ppl_vert_len);
osgcpe::resource::Resource textureImage("images", "digit.png", digit_png, digit_png_len);
osgcpe::scene::textureImageScene(shaderFrag, shaderVert, textureImage, scene);
