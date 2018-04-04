# Table of contents

* [Overview](#overview)
* [Examples](#examples)
  * [01. Embed resources into executable](#examples-embed-resources)
  * [02. Use images with PNG/ImageIO plugins](#examples-images)
* [Help](#help)

<a name="overview"/>

# Overview

[OpenSceneGraph](http://openscenegraph.org) is an open source high performance
3D graphics toolkit, used by application developers in fields such as visual
simulation, games, virtual reality, scientific visualization and modelling.

This document is a collection of examples that take you from where
[OpenSceneGraph cross-platform guide][osgcpg] left you.

Please note that these are only examples, not tutorials. As such, there are no videos and
explanations are much shorter and with less screenshots.

Each example is a complete application that runs on the following platforms:

* Linux
* macOS
* Windows
* Android
* iOS
* Web

<a name="examples"/>

# Examples

<a name="examples-embed-resources"/>

### [01. Embed resources into executable](01/README.md)

  ![Screenshot](01/shot.png)

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

