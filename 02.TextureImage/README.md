
# Table of contents

* [Overview](#overview)
* [Steps](#steps)
    * [2.1. Generate resources](#generate)
    * [2.2. OpenSceneGraph support for PNG](#plugins)
    * [2.3. Provide shader resources as strings](#shaders)
    * [2.4. Provide image resource as a texture](#image)
    * [2.5. Apply shaders and texture to the scene](#scene)
* [Result](#result)

<a name="overview"/>

# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we use PNG image as a texture for a model. All resources are
embedded into application.

**Note**: this example requires [01.EmbedResource example][ex01] knowledge.

<a name="steps"/>

# Steps

<a name="generate"/>

## 2.1. Generate resources

We need to have the following files generated:

* `ppl.frag.h`: per-pixel lighting fragment shader
* `ppl.vert.h`: per-pixel lighting vertex shader
* `digit.png.h`: image to use as a texture

**Note**: see [01.EmbedResource][ex01] for details on resource generation and embedding.

<a name="plugins"/>

## 2.2. OpenSceneGraph support for PNG

OpenSceneGraph has two plugins capable of loading PNG images:

* `png`
    * uses [libpng][libpng] library
    * available for all platforms
    * plugin file: `osgdb_png.so` or `libosgdb_png.a`
    * linking in CMakeLists.txt:
        ```
        - - - -
        TARGET_LINK_LIBRARIES(
        - - - -
            osgdb_png
            png
        - - - -
        ```
* `imageio`
    * uses [Image I/O][imageio] library
    * only available for Apple platforms
    * plugin file: `osgdb_imageio.so` or `libosgdb_imageio.a`
    * linking in CMakeLists.txt:
        ```
        - - - -
        TARGET_LINK_LIBRARIES(
        - - - -
            osgdb_imageio
            imageio
        - - - -
        ```

As you can see, only macOS and iOS builds use `imageio` plugin. Other builds
use `png` one.

**Notes**:

* Android build uses [libpng-android][libpng-android]
* Web build uses `libpng` provided by [Emscripten][emscripten], so we simply
provide necessary build flags ([source code][emscripten-png]):
    * `-s USE_LIBPNG=1`
    * `-s USE_ZLIB=1`

<a name="shaders"/>

## 2.3. Provide shader resources as strings

[01.EmbedResource][ex01] example provides shaders in code.
This works fine for single line shaders. 

Now that we need more complex shaders to apply textures, it's easier to manage
shaders separately from application's source code. That's why shaders are now
resources.

Let's see how to convert a resource to a string ([source code][resource-to-string]):

```
std::string string(const Resource &resource)
{
    const char *contents = reinterpret_cast<const char *>(resource.contents);
    return std::string(contents, resource.len);
}
```

**Note**: we cast `unsigned char *` (originally provided by `xxd`) to
`const char *`.

Let's see how to provide shader resources as strings to other functions
([source code][resource-string-usage]):

```
// Create shader program.
auto prog =
    render::createShaderProgram(
        resource::string(shaderVert),
        resource::string(shaderFrag)
    );
```

Finally, `shaderVert` and `shaderFrag` are defined like this
([source code][shaders-definition]):

```
resource::Resource shaderFrag("shaders", "ppl.frag", ppl_frag, ppl_frag_len);
resource::Resource shaderVert("shaders", "ppl.vert", ppl_vert, ppl_vert_len);
```

<a name="image"/>

## 2.4. Provide image resource as a texture

First, we need to read an image from a resource. Here's how the crucial part
of the implementation looks like ([source code][resource-setTextureImage]):

```
- - - -
auto reader =
    osgDB::Registry::instance()->getReaderWriterForExtension(ex);
if (reader)
{
    ResourceStreamBuffer buf(resource);
    std::istream in(&buf);
    auto result = reader->readImage(in, 0);
    if (result.success())
    {
        texture->setImage(result.getImage());
    }
- - - -
```

**Note**: we do not return the image outside the function because the image
gets deallocated by that time, that's why we use the image before leaving the scope.

Second, we need to create a texture with that image
([source code][resource-createTexture]):

```
osg::Texture2D *createTexture(const Resource &resource)
{
    osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
    setTextureImage(tex, resource);
    tex->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT);
    tex->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::REPEAT);
    tex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
    tex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    return tex.release();
}
```

<a name="scene"/>

## 2.5. Apply shaders and texture to the scene

The last step is to get scene's material and apply shaders with texture to
the material ([source code][scene-textureImageScene]):

```
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
```

<a name="result"/>

# Result

![Screenshot](shot.png)

Here's a [web build of the example][web-build].

[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
[osgcpg]: https://github.com/OGStudio/openscenegraph-cross-platform-guide
[ex01]: ../01.EmbedResource
[libpng]: http://www.libpng.org/pub/png/libpng.html
[imageio]: https://developer.apple.com/documentation/imageio
[libpng-android]: https://github.com/julienr/libpng-android
[emscripten]: http://emscripten.org/
[emscripten-png]: web/CMakeLists.txt#L29
[resource-to-string]: desktop/src/resource.h#L177
[resource-string-usage]: desktop/src/scene.h#L44
[shaders-definition]: desktop/src/main.h#L276
[resource-setTextureImage]: desktop/src/resource.h#L184
[resource-createTexture]: desktop/src/resource.h#L242
[scene-textureImageScene]: desktop/src/scene.h#L44
[web-build]: https://ogstudio.github.io/openscenegraph-cross-platform-examples-web-builds/examples/02/ex02-texture-image.html
