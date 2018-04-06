# Table of contents

* [Overview](#overview)
* [How to build](#build)
* [Examples](#examples)
  * [01. Embed resource into executable](#examples-embed-resource)
  * [02. Load PNG images with PNG/ImageIO plugins](#examples-images)
* [Help](#help)

<a name="overview"/>

# Overview

[OpenSceneGraph](http://openscenegraph.org) is an open source high performance
3D graphics toolkit, used by application developers in fields such as visual
simulation, games, virtual reality, scientific visualization and modelling.

This document is a collection of examples to perform specific tasks. This
document is a logical continuation of [OpenSceneGraph cross-platform guide][osgcpg], which
can be seen as an introduction to working with OpenSceneGraph.

This document, unlike [OpenSceneGraph cross-platform guide][osgcpg], only contains examples,
not tutorials with screenshots and videos. Here, you find a solution for a specific
problem only.

Examples run on the following platforms:

* Linux
* macOS
* Windows
* Android
* iOS
* Web

**Note**: please, make yourself familiar with [OpenSceneGraph cross-platform guide][osgcpg]
before trying examples.

<a name="build"/>

# How to build

Each example contains four implementations to cover all supported platforms:

* desktop (Linux, macOS, Windows)
* android
* ios
* web

## Desktop

  ![Screenshot](shot-desktop.png)

**Note**: you must have OpenSceneGraph installation. See [OpenSceneGraph cross-platform guide][osgcpg] for details.

To build `01.EmbedResource` example for desktop, run the following commands:

```
cd 01.EmbedResource/desktop
mkdir build
cd build
cmake ..
make
```

To launch the first example, run the following command:

`./ex01-embed-resource`

## Android

**Notes**:

* You must have OpenSceneGraph sources alongside this repository clone (see [OpenSceneGraph cross-platform guide][osgcpg] for details)
* Android project is built for `armeabi-v7a` architecture by default (update `abiFilters` value in `android/app/build.gradle` if you want other platforms)

To build and run `01.EmbedResource` example for Android, you open
`01.EmbedResource/android` in Android Studio and run the project.


**Note**: all examples require:

* knowledge of [OpenSceneGraph cross-platform guide][osgcpg]
* OpenSceneGraph installation for desktop builds
* OpenSceneGraph sources (located alongside this repository clone) for other platforms

<a name="examples"/>

# Examples

<a name="examples-embed-resources"/>

### [01. Embed resources into executable](01.EmbedResource/README.md)

  ![Screenshot](01.EmbedResource/shot.png)

  Learn how to use `xxd` Unix utility to convert any binary file (in our case,
  it's box.osgt model) into
  C header file and use it across platforms with OpenSceneGraph.

<a name="examples-images"/>

### [02. Use images with PNG/ImageIO plugins](02.Images)

  ![Screenshot](02.Images/shot.png)

  Learn how to build PNG/ImageIO plugins across platforms and reference built-in
  PNG images using simple shaders.

<a name="help"/>

Help
====

Feel free to [ask questions][issues] in the issues. Your questions help us
improve examples.

[osgcpg]: https://github.com/OGStudio/openscenegraph-cross-platform-guide
[issues]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/issues

