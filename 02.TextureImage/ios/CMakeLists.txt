PROJECT(EX02_TEXTURE_IMAGE)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(BUILD_SIMULATOR YES CACHE BOOL "Build for simulator. Set to `false` to build for real device")

# Path to external projects:
# * OpenSceneGraph
SET(EXT_PROJ_DIR "${CMAKE_SOURCE_DIR}/../../..")

# Set special build flags:
# * -O3: make compact binary, critical for iOS
# * -mios-simulator-version-min=9.0: specify minimal target iOS version, critical for 32-bit builds
SET(BUILD_FLAGS "-O3 -mios-simulator-version-min=9.0")
ADD_DEFINITIONS(${BUILD_FLAGS})

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Specify critical OpenSceneGraph build variables.
SET(OPENGL_PROFILE "GLES2" CACHE STRING "OpenGL variant to use")
SET(DYNAMIC_OPENTHREADS OFF CACHE BOOL "Link OpenThreads statically")
SET(DYNAMIC_OPENSCENEGRAPH OFF CACHE BOOL "Link OpenSceneGraph statically")
SET(BUILD_OSG_APPLICATIONS OFF CACHE BOOL "Do not build OpenSceneGraph samples")
# Configure OpenSceneGraph for simulator or real device.
IF(BUILD_SIMULATOR)
    # Prevent macOS SDK includes that lead to build errors.
    SET(CURL_INCLUDE_DIR "" CACHE STRING "Prevent wrong macOS SDK include" FORCE)
    SET(ZLIB_INCLUDE_DIR "" CACHE STRING "Prevent wrong macOS SDK include" FORCE)
    SET(OSG_BUILD_PLATFORM_IPHONE_SIMULATOR YES CACHE BOOL "Build OpenSceneGraph for simulator")
    SET(IOS_PLATFORM "iPhoneSimulator")
ELSE()
    SET(OSG_BUILD_PLATFORM_IPHONE YES CACHE BOOL "Build OpenSceneGraph for device")
    SET(IPHONE_VERSION_MIN "9.0")
    SET(IOS_PLATFORM "iPhoneOS")
ENDIF()
# Build and reference OpenSceneGraph.
IF(BUILD_SIMULATOR)
    SET(BUILD_VARIANT "Simulator")
ELSE()
    SET(BUILD_VARIANT "Device")
ENDIF()
SET(OSG_SOURCE_DIR "${EXT_PROJ_DIR}/OpenSceneGraph" CACHE PATH "Path to OpenSceneGraph source directory")
SET(OSG_BUILD_DIR "${OSG_SOURCE_DIR}/build/${BUILD_VARIANT}/Ex02")
# Only build OpenSceneGraph if it has not yet been built.
IF (NOT EXISTS "${OSG_BUILD_DIR}/lib/libosgdb_imageio.a")
    FILE(MAKE_DIRECTORY ${OSG_BUILD_DIR})
    ADD_SUBDIRECTORY(${OSG_SOURCE_DIR} ${OSG_BUILD_DIR})
ENDIF ()
# Reference OpenSceneGraph includes.
INCLUDE_DIRECTORIES(${OSG_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${OSG_BUILD_DIR}/include)

# Override iOS SDK path. Must to it after OpenSceneGraph configuration.
SET(DEV_PLATFORMS "/Applications/Xcode.app/Contents/Developer/Platforms")
SET(SDK_ROOT "${DEV_PLATFORMS}/${IOS_PLATFORM}.platform/Developer/SDKs/${IOS_PLATFORM}.sdk")
SET(CMAKE_OSX_SYSROOT ${SDK_ROOT} CACHE STRING "Make sure we build for iOS" FORCE)

# Reference source headers.
INCLUDE_DIRECTORIES(src)
# Reference resource headers.
INCLUDE_DIRECTORIES(../../data)
# Build example library.
ADD_LIBRARY(rawex02 STATIC src/library.cpp)
# NOTE This does not actually link anything. However, this command
# NOTE makes sure all necessary libraries are built.
TARGET_LINK_LIBRARIES(
    rawex02
    osgViewer
    osgDB
    # osgDB plugins start.
    osgdb_imageio
    osgdb_osg
    osgdb_serializers_osg
    # osgDB plugins end.
    osgGA
    osgShadow
    osgText
    osgUtil
    osg
    OpenThreads
)

IF(BUILD_SIMULATOR)
    SET(BUILD_SUFFIX "Release-iphonesimulator")
ELSE()
    SET(BUILD_SUFFIX "Release-iphoneos")
ENDIF()
# Generate single ex02 library once rawex02 one has been built.
ADD_CUSTOM_COMMAND(
    TARGET rawex02
    POST_BUILD
    #COMMAND "${CMAKE_SOURCE_DIR}/create_single_osglib" "." "${OSG_BUILD_DIR}"
    COMMAND
        "libtool"
        "-static" 
        "-o"
        "libex02.a"
        "${CMAKE_BINARY_DIR}/${BUILD_SUFFIX}/librawex02.a"
        "${OSG_BUILD_DIR}/lib/libosg.a"
        "${OSG_BUILD_DIR}/lib/libosgDB.a"
        "${OSG_BUILD_DIR}/lib/libosgdb_imageio.a"
        "${OSG_BUILD_DIR}/lib/libosgdb_osg.a"
        "${OSG_BUILD_DIR}/lib/libosgdb_serializers_osg.a"
        "${OSG_BUILD_DIR}/lib/libosgGA.a"
        "${OSG_BUILD_DIR}/lib/libosgShadow.a"
        "${OSG_BUILD_DIR}/lib/libosgText.a"
        "${OSG_BUILD_DIR}/lib/libosgUtil.a"
        "${OSG_BUILD_DIR}/lib/libosgViewer.a"
        "${OSG_BUILD_DIR}/lib/libOpenThreads.a"
)

