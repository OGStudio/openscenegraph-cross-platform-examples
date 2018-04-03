CMAKE_MINIMUM_REQUIRED(VERSION 3.4.1)

# Path to external projects:
# * OpenSceneGraph
SET(EXT_PROJ_DIR "${CMAKE_SOURCE_DIR}/../../../..")

# Specify critical OpenSceneGraph build variables.
SET(OPENGL_PROFILE "GLES2" CACHE STRING "OpenGL variant to use")
SET(DYNAMIC_OPENTHREADS OFF CACHE BOOL "Link OpenThreads statically")
SET(DYNAMIC_OPENSCENEGRAPH OFF CACHE BOOL "Link OpenSceneGraph statically")
# Reference OpenSceneGraph.
SET(OSG_SOURCE_DIR "${EXT_PROJ_DIR}/OpenSceneGraph")
SET(OSG_BUILD_DIR "${OSG_SOURCE_DIR}/build/Android-${ANDROID_ABI}")
# Only build OpenSceneGraph if it has not yet been built.
IF (NOT EXISTS "${OSG_BUILD_DIR}/lib/libosgViewer.a")
    FILE(MAKE_DIRECTORY ${OSG_BUILD_DIR})
    ADD_SUBDIRECTORY(${OSG_SOURCE_DIR} ${OSG_BUILD_DIR})
ENDIF ()
# Reference OpenSceneGraph includes.
INCLUDE_DIRECTORIES(${OSG_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${OSG_BUILD_DIR}/include)
# Reference OpenSceneGraph libraries.
LINK_DIRECTORIES(${OSG_BUILD_DIR}/lib)

ADD_LIBRARY(library SHARED src/main/cpp/library.cpp)
FIND_LIBRARY(log-lib log)
# Libraries must be linked in the specified order.
# Otherwise you may get unsatisified linker errors.
TARGET_LINK_LIBRARIES(
    library
    ${log-lib}
    GLESv2
    osgViewer
    osgDB
    z
    # osgDB plugins start.
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

