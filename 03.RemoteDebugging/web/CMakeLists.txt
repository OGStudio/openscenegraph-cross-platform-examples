PROJECT(EX03_REMOTE_DEBUGGING)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Path to external projects:
# * OpenSceneGraph
# * NLohmann's json
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
# * -s USE_LIBPNG=1: use libpng
# * -s USE_ZLIB=1: use zlib, necessary for libpng
# * -s FETCH=1: use FetchAPI for HTTP(s) requests
SET(BUILD_FLAGS "-O3 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -s USE_LIBPNG=1 -s USE_ZLIB=1 -s FETCH=1")
ADD_DEFINITIONS(${BUILD_FLAGS})
# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Force PNG detection.
SET(PNG_PNG_INCLUDE_DIR "whatever" CACHE STRING "Force PNG detection")
SET(PNG_LIBRARY "libpng" CACHE STRING "Force PNG detection")
SET(ZLIB_INCLUDE_DIR "whatever" CACHE STRING "Force ZLIB detection")
SET(ZLIB_LIBRARY "zlib" CACHE STRING "Force ZLIB detection")
SET(OSG_CPP_EXCEPTIONS_AVAILABLE ON CACHE BOOL "Force PNG plugin building")

SET(OSG_SOURCE_DIR "${EXT_PROJ_DIR}/OpenSceneGraph")
SET(OSG_BUILD_DIR "${OSG_SOURCE_DIR}/build/Emscripten")
# Only build OpenSceneGraph if it has not yet been built.
IF (NOT EXISTS "${OSG_BUILD_DIR}/lib/libosgdb_png.a")
    FILE(MAKE_DIRECTORY ${OSG_BUILD_DIR})
    ADD_SUBDIRECTORY(${OSG_SOURCE_DIR} ${OSG_BUILD_DIR})
ENDIF ()
# Reference OpenSceneGraph includes.
INCLUDE_DIRECTORIES(${OSG_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${OSG_BUILD_DIR}/include)
# Reference OpenSceneGraph libraries.
LINK_DIRECTORIES(${OSG_BUILD_DIR}/lib)

# Reference NLohmann's JSON parsing library.
INCLUDE_DIRECTORIES(${EXT_PROJ_DIR}/json/single_include)

# Reference source headers.
INCLUDE_DIRECTORIES(src)
# Reference resource headers.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../../data)
# Create executable (aka HTML page).
ADD_EXECUTABLE(ex03-remote-debugging src/main.cpp)
# Link with OpenSceneGraph libraries in specific order.
# Otherwise you may get unsatisified linker errors.
TARGET_LINK_LIBRARIES(
    ex03-remote-debugging
    osgViewer
    osgDB
    # osgDB plugins start.
    osgdb_osg
    osgdb_serializers_osg
    osgdb_png
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
SET_TARGET_PROPERTIES(ex03-remote-debugging PROPERTIES LINK_FLAGS ${BUILD_FLAGS})
