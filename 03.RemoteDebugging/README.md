
# Table of contents

* [Overview](#overview)
* [Steps](#steps)
    * [3.1. ](#generate)
    * [3.2. network?](#plugins)
        * [](#)
    * [3.3. ](#shaders)
* [Result](#result)

<a name="overview"/>

# Overview

This example is part of [OpenSceneGraph cross-platform examples][osgcpe].

In this example we use PNG image as a texture for a model. All resources are
embedded into application.

**Non-desktop platforms' note**: don't forget to reference OpenSceneGraph plugins with `USE_OSGPLUGIN` macro.

<a name="steps"/>

# Steps

<a name="generate"/>

## 2.1. Generate resources

We need to have the following files generated:

* `ppl.frag.h`: per-pixel lighting fragment shader
* `ppl.vert.h`: per-pixel lighting vertex shader
* `digit.png.h`: image to use as a texture

**Note**: see [01.EmbedResource][ex01] for details on resource generation and embedding.

<a name="result"/>

# Result

![Screenshot](shot.png)

Here's a [web build of the example][web-build].

[osgcpe]: https://github.com/OGStudio/openscenegraph-cross-platform-examples
