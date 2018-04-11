
# Table of contents

* [Overview](#overview)
* [Steps](#steps)
    * [1.1. Generate resources](#generate)
    * [1.2. Rebuild OpenSceneGraph with PNG support](#rebuild)
    * [1.3. Provide shader resources as strings](#shaders)
    * [1.4. Provide image resource as a texture](#image)
    * [1.5. Apply shaders and image to texture the scene](#scene)
* [Result](#result)

<a name="overview"/>

# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we use PNG image as a texture for a model. All resources are
embedded into application.

<a name="steps"/>

# Steps

<a name="generate"/>

## 1.1. Generate resources

We need to have the following files generated:

* `ppl.frag.h`: per-pixel lighting fragment shader
* `ppl.vert.h`: per-pixel lighting vertex shader
* `digit.png.h`: image to use as a texture

**Note**: see [01.EmbedResource][ex01] for details on resource generation and embedding.

<a name="rebuild"/>

## 1.2. Rebuild OpenSceneGraph with PNG support

OpenSceneGraph has two plugins capable of loading PNG images:

* `png`
    * uses [libpng][libpng] library
    * available for all platforms
    * plugin file: `osgdb_png.so` or `osgdb_png.a`
* `imageio`
    * uses [Image I/O][imageio] library
    * only available for Apple platforms
    * plugin file: `osgdb_imageio.so` or `osgdb_imageio.a`

**macOS, iOS note**: since Apple provides [Image I/O][imageio] library to work
with popular image formats, you don't need to use any additional dependency to
work with PNG.

### Linux, Windows

You should generally use package managers ([MSYS2][msys2] for Windows) to install
OpenSceneGraph because they provide OpenSceneGraph with `png` plugin by default.

If you build OpenSceneGraph from sources, you need to make sure `libpng` is found
by `CMake` during configuration stage. Consult `CMake`'s [FindPNG][find_png] documentation
for details.

### macOS

If you installed OpenSceneGraph with [brew][brew], you already have
`imageio` plugin installed.

If you built OpenSceneGraph from sources, `CMake` should have found `Image I/O`
during configuration stage.

### iOS

To use `Image I/O` on iOS, you need to link your application with
`ImageIO.framework`.

TODO Verify

### Android

TODO Describe `libpng-android` library building and installation, OSG rebuilding.

### Web

TODO Describe build flags to enable PNG support during OSG rebuilding.


<a name="shaders"/>

## 1.3. Provide shader resources as strings

[01.EmbedResource][ex01] example provided shaders as simple [strings][ex01_shaders].
This worked fine for single line shaders. 

Now that we need more complex shaders to apply textures, it's easier to manage
them separately from application's source code. That's why shaders are now
resources.

Let's see how to convert a resource to a string ([source code][resources_string]):

```
std::string string(const Resource &resource)
{
    const char *contents = reinterpret_cast<const char *>(resource.contents);
    return std::string(contents, resource.len);
}
```

**Note**: we casted `unsigned char *` (originally provided by `xxd`) to
`const char *`.


Let's see how to provide shader resources as strings to other functions
([source code][resources_string_usage]):

```
// Create shader program.
auto prog =
    render::createShaderProgram(
        resources::string(shaderVert),
        resources::string(shaderFrag)
    );
```

Finally, `shaderVert` and `shaderFrag` are defined like this
([source code][shaders_definition]):

```
osgcpe::Resource shaderFrag("shaders", "ppl.frag", ppl_frag, ppl_frag_len);
osgcpe::Resource shaderVert("shaders", "ppl.vert", ppl_vert, ppl_vert_len);
```

<a name="load"/>

## 1.4. ...

TODO:

* describe resources::setTextureImage
* describe resources::createTexture
* describe scene::textureImageScene
* describe Example+TextureImageScene

<a name="result"/>

# Result

![Screenshot](shot.png)

Here's a [web build of the example][web_build].

[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
[osgcpg]: https://github.com/OGStudio/openscenegraph-cross-platform-guide
[ex01]: ../01.EmbedResource/README.md
[libpng]: http://www.libpng.org/pub/png/libpng.html
[imageio]: https://developer.apple.com/documentation/imageio
[msys2]: https://www.msys2.org/
[find_png]: https://cmake.org/cmake/help/v3.0/module/FindPNG.html
[brew]: https://brew.sh/
[ex01_shaders]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/01.EmbedResource/desktop/src/scene.h#L37
[resources_string]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/02.TextureImage/desktop/src/resources.h#L126
[resources_string_usage]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/02.TextureImage/desktop/src/scene.h#L45
[shaders_definition]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/blob/master/02.TextureImage/desktop/src/Example.h#L81
