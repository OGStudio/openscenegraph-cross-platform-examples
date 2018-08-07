PROJECT(IOS_GEN)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(BUILD_SIMULATOR YES CACHE BOOL "Build for simulator. Set to `false` to build for real device")

# Path to external projects:
# * OpenSceneGraph
SET(OSG_DIR "${CMAKE_SOURCE_DIR}/../../../../../../OpenSceneGraph")

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
SET(OSG_SOURCE_DIR "${OSG_DIR}" CACHE PATH "Path to OpenSceneGraph source directory")
SET(OSG_BUILD_DIR "${OSG_DIR}/build/${BUILD_VARIANT}")

FILE(MAKE_DIRECTORY ${OSG_BUILD_DIR})
ADD_SUBDIRECTORY(${OSG_SOURCE_DIR} ${OSG_BUILD_DIR})
INCLUDE_DIRECTORIES(${OSG_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${OSG_BUILD_DIR}/include)

# Override iOS SDK path. Must to it after OpenSceneGraph configuration.
SET(DEV_PLATFORMS "/Applications/Xcode.app/Contents/Developer/Platforms")
SET(SDK_ROOT "${DEV_PLATFORMS}/${IOS_PLATFORM}.platform/Developer/SDKs/${IOS_PLATFORM}.sdk")
SET(CMAKE_OSX_SYSROOT ${SDK_ROOT} CACHE STRING "Make sure we build for iOS" FORCE)

# Build sample.
ADD_LIBRARY(gen STATIC gen.cpp)
