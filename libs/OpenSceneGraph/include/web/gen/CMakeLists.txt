PROJECT(WEB_GEN)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Path to external projects:
# * OpenSceneGraph
SET(EXT_PROJ_DIR "${CMAKE_SOURCE_DIR}/../../../../../..")

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

SET(OSG_SOURCE_DIR "${EXT_PROJ_DIR}/OpenSceneGraph")
#SET(OSG_BUILD_DIR "${OSG_SOURCE_DIR}/build/Emscripten")
SET(OSG_BUILD_DIR "${CMAKE_BINARY_DIR}/emscripten")
# Only build OpenSceneGraph if it has not yet been built.
IF (NOT EXISTS "${OSG_BUILD_DIR}/lib/libosgdb_png.a")
    FILE(MAKE_DIRECTORY ${OSG_BUILD_DIR})
    ADD_SUBDIRECTORY(${OSG_SOURCE_DIR} ${OSG_BUILD_DIR})
ENDIF ()

ADD_EXECUTABLE(test main.cpp)
