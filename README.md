# Table of contents

* [Overview](#overview)
* [How to build](#build)
    * [Desktop](#build-desktop)
    * [Android](#build-android)
    * [iOS](#build-ios)
    * [Web](#build-web)
* [Examples](#examples)
    * [01. Embed resource into executable](#ex01)
    * [02. Use PNG images with PNG plugins](#ex02)
    * [03. Debug application remotely](#ex03)
* [Help](#help)

<a name="overview"/>

# Overview

[OpenSceneGraph][osg] is an open source high performance
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

**Plugin notes**:

* desktop builds
    * OpenSceneGraph plugins are referenced at run-time
    * plugins should be located in a directory where dynamic linker looks for libraries
* non-desktop builds
    * OpenSceneGraph plugins are linked with at build time
    * plugins should be explicitely referenced in code with `USE_OSGPLUGIN` macro

<a name="build-desktop"/>

## Desktop

  ![Screenshot][screenshot-desktop]

**Notes**:

* you must have OpenSceneGraph installation (see [OpenSceneGraph cross-platform guide][osgcpg] for details)
* you may need to specify OpenSceneGraph include and library directories with `-DOSG_INC_DIR=/path/to/OSG/includes` and `-DOSG_LIB_DIR=/path/to/OSG/libs` during `cmake` invocation if OpenSceneGraph is located in non-standard location

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

<a name="build-android"/>

## Android

  ![Screenshot][screenshot-android]

**Notes**:

* you must have OpenSceneGraph sources alongside this repository clone (see [OpenSceneGraph cross-platform guide][osgcpg] for details)
* Android project is built for `armeabi-v7a` architecture by default (update `abiFilters` value in `android/app/build.gradle` if you want other platforms)
* make sure to run `Tools -> Android -> Sync Project with Gradle Files` in Android Studio after opening each example, this is necessary for Android Studio to create internal project files
* each example builds its own version of OpenSceneGraph under `/path/to/OpenSceneGraph/build/Android-<ABI>/Ex<Number>` because different examples require different OpenSceneGrah plugins

To build and run `01.EmbedResource` example for Android, you open
`01.EmbedResource/android` in Android Studio and run the project.

<a name="build-ios"/>

## iOS

  ![Screenshot][screenshot-ios]

**Notes**:

* you must have OpenSceneGraph sources alongside this repository clone (see [OpenSceneGraph cross-platform guide][osgcpg] for details)
* each example builds its own version of OpenSceneGraph under `/path/to/OpenSceneGraph/build/<Device|Simulator>/Ex<Number>` because different examples require different OpenSceneGrah plugins

First, build example library (for each example) for Simulator and Device:

```
cd 01.EmbedResource/ios

# Simulator.
mkdir -p build/Simulator
cd build/Simulator
cmake -G Xcode -DIPHONE_ENABLE_BITCODE=YES ../..
cmake --build . --config Release -- -IDEBuildOperationMaxNumberOfConcurrentCompileTasks=8

cd ../..

# Device.
mkdir -p build/Device
cd build/Device
cmake -G Xcode -DIPHONE_ENABLE_BITCODE=YES -DBUILD_SIMULATOR=NO ../..
cmake --build . --config Release -- -IDEBuildOperationMaxNumberOfConcurrentCompileTasks=8
```

**Build issues**:

* if you encounter `Undefined symbols for architecture <Arch>` errors with `library::`
    * remove OpenSceneGraph build and retry
* if some plugins cannot be built either due to missing headers (like curl), or wrong `-std=c++11` directive
    * rerun `cmake .` to refresh CMake cache files
    * retry the build command to make sure `rawex` iOS library has been built
* you may also build missing libraries and plugins manually by appending `-target` to `cmake` command, e.g., `-target osgdb_osg` 

Second, open `01.EmbedResource/ios/xcodeproject/ex01.xcodeproj` Xcode project and run it.

<a name="build-web"/>

## Web

  ![Screenshot][screenshot-web]

**Note**: you must have OpenSceneGraph sources alongside this repository clone (see [OpenSceneGraph cross-platform guide][osgcpg] for details)

To build `01.EmbedResource` example for web, run the following commands:

```
cd 01.EmbedResource/web
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/emsdk-portable/emscripten/<version>/cmake/Modules/Platform/Emscripten.cmake ..
make -j8 ex01-embed-resource
```

To launch the first example, open `ex01-embed-resource.html` file in Firefox.

To launch examples in any web browser, you need to serve the files with a web server.
E.g., you can serve locally like this:

* serve with the following commands:
    ```
    cd 01.EmbedResource/web/build
    python -m SimpleHTTPServer
    ```
* open [http://localhost:8000](http://localhost:8000) in any web browser

<a name="examples"/>

# Examples

<a name="ex01"/>

### [01. Embed resource into executable][ex01]

  ![Screenshot][ex01-screenshot]

  Learn how to embed a binary resource into application with `xxd` Unix utility
  and use the resource across platforms.

<a name="ex02"/>

### [02. Use PNG images with PNG plugins][ex02]

  ![Screenshot][ex02-screenshot]

  Learn how to use PNG images across platforms with PNG plugins.

<a name="ex03"/>

### [03. Debug application remotely][ex03]

  ![Screenshot][ex03-screenshot]

  Learn how to work with debug-broker to perform remote debugging.

<a name="help"/>

Help
====

Feel free to [ask questions][issues] in the issues. Your questions help us
improve examples.

[osg]: http://openscenegraph.org
[osgcpg]: https://github.com/OGStudio/openscenegraph-cross-platform-guide
[issues]: https://github.com/OGStudio/openscenegraph-cross-platform-examples/issues
[screenshot-desktop]: readme/shot-desktop.png
[screenshot-android]: readme/shot-android.png
[screenshot-ios]: readme/shot-ios.png
[screenshot-web]: readme/shot-web.png

[ex01]: 01.EmbedResource
[ex01-screenshot]: 01.EmbedResource/shot.png

[ex02]: 02.TextureImage
[ex02-screenshot]: 02.TextureImage/shot.png

[ex03]: 03.RemoteDebugging
[ex03-screenshot]: 03.RemoteDebugging/shot.png
