PROJECT(EXAMPLE_EMBED_RESOURCE)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Path to external projects:
# * OpenSceneGraph
SET(EXT_PROJ_DIR "${CMAKE_SOURCE_DIR}/../../..")

# Specify critical OpenSceneGraph build variables.
SET(BUILD_OSG_APPLICATIONS NO CACHE BOOL "Do not build applications")
SET(EGL_LIBRARY "GL" CACHE STRING "Suppress linkage error")
SET(OSG_GL1_AVAILABLE OFF CACHE BOOL "Unavailable under Emscripten")
SET(OSG_GL2_AVAILABLE OFF CACHE BOOL "Unavailable under Emscripten")
SET(OSG_GLES2_AVAILABLE ON CACHE BOOL "GLES2 is what Emscripten uses")
SET(OSG_WINDOWING_SYSTEM "None" CACHE STRING "Unavailable under Emscripten")
SET(DYNAMIC_OPENTHREADS OFF CACHE BOOL "Link OpenThreads statically")
SET(DYNAMIC_OPENSCENEGRAPH OFF CACHE BOOL "Link OpenSceneGraph statically")
# Prevent CMake error during configuration.
SET(_OPENTHREADS_ATOMIC_USE_GCC_BUILTINS_EXITCODE "0" CACHE STRING "Prevent cfg error")

# Set special build flags:
# * -O3: make compact binary, critical for web
# * -s USE_SDL=2: provide SDL2
# * -s ALLOW_MEMORY_GROWTH=1: allow total memory used to increase when necessary
SET(BUILD_FLAGS "-O3 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1")
#SET(BUILD_FLAGS "-O3 -s FULL_ES2=1 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1")
ADD_DEFINITIONS(${BUILD_FLAGS})
# Use C++11.
ADD_DEFINITIONS("-std=c++11")

SET(OSG_SOURCE_DIR "${EXT_PROJ_DIR}/OpenSceneGraph")
SET(OSG_BUILD_DIR "${EXT_PROJ_DIR}/OpenSceneGraph/build/Emscripten")
# Only build OpenSceneGraph if it has not yet been built.
IF (NOT EXISTS "${OSG_BUILD_DIR}/lib/libosg.a")
    FILE(MAKE_DIRECTORY ${OSG_BUILD_DIR})
    ADD_SUBDIRECTORY(${OSG_SOURCE_DIR} ${OSG_BUILD_DIR})
ENDIF ()
# Reference OpenSceneGraph includes.
INCLUDE_DIRECTORIES(${OSG_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${OSG_BUILD_DIR}/include)
# Reference OpenSceneGraph libraries.
LINK_DIRECTORIES(${OSG_BUILD_DIR}/lib)

# Reference headers.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
# Reference resource headers.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../../data)
# Create executable (aka HTML page).
ADD_EXECUTABLE(exampleEmbedResource src/main.cpp)
# Link with OpenSceneGraph libraries in specific order.
# Otherwise you may get unsatisified linker errors.
TARGET_LINK_LIBRARIES(
    exampleEmbedResource
    osgViewer
    osgDB
    # osgDB plugins start.
    osgdb_osg
    osgdb_serializers_osg
    # osgDB plugins end.
    osgGA
    osgText
    osgUtil
    osg
    OpenThreads
)

# Make Emscripten generate ready-to-open HTML page.
SET(CMAKE_EXECUTABLE_SUFFIX ".html")
# Link with special build flags.
SET_TARGET_PROPERTIES(exampleEmbedResource PROPERTIES LINK_FLAGS ${BUILD_FLAGS})
