PROJECT(EX01_EMBED_RESOURCE)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Build OpenSceneGraph statically.
INCLUDE(../../libs/OpenSceneGraph/CMakeLists.txt)

# Set special build flags:
# * -O3: make compact binary, critical for web
# * -s USE_SDL=2: provide SDL2
# * -s ALLOW_MEMORY_GROWTH=1: allow total memory used to increase when necessary
SET(BUILD_FLAGS "-O3 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1")
ADD_DEFINITIONS(${BUILD_FLAGS})

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Specify critical OpenSceneGraph build variables.
#SET(BUILD_OSG_APPLICATIONS NO CACHE BOOL "Do not build applications")
#SET(EGL_LIBRARY "GL" CACHE STRING "Suppress linkage error")
#SET(OSG_GL1_AVAILABLE OFF CACHE BOOL "Unavailable under Emscripten")
#SET(OSG_GL2_AVAILABLE OFF CACHE BOOL "Unavailable under Emscripten")
#SET(OSG_GLES2_AVAILABLE ON CACHE BOOL "GLES2 is what Emscripten uses")
#SET(OSG_WINDOWING_SYSTEM "None" CACHE STRING "Unavailable under Emscripten")
#SET(DYNAMIC_OPENTHREADS OFF CACHE BOOL "Link OpenThreads statically")
#SET(DYNAMIC_OPENSCENEGRAPH OFF CACHE BOOL "Link OpenSceneGraph statically")
# Prevent CMake error during configuration.
#SET(_OPENTHREADS_ATOMIC_USE_GCC_BUILTINS_EXITCODE "0" CACHE STRING "Prevent cfg error")

# Reference source headers.
INCLUDE_DIRECTORIES(src)
# Reference resource headers.
INCLUDE_DIRECTORIES(../../data)
# Create executable (aka HTML page).
ADD_EXECUTABLE(ex01-embed-resource src/main.cpp)
# Link with OpenSceneGraph libraries in specific order.
# Otherwise you may get unsatisified linker errors.
TARGET_LINK_LIBRARIES(
    ex01-embed-resource
    osgViewer
    osgDB
    # osgDB plugins start.
    osgdb_osg
    osgdb_serializers_osg
    # osgDB plugins end.
    osgGA
    osgUtil
    osg
    OpenThreads
)
#osgText

# Make Emscripten generate ready-to-open HTML page.
SET(CMAKE_EXECUTABLE_SUFFIX ".html")
# Link with special build flags.
SET_TARGET_PROPERTIES(ex01-embed-resource PROPERTIES LINK_FLAGS ${BUILD_FLAGS})
