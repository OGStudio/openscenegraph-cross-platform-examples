CMAKE_MINIMUM_REQUIRED(VERSION 3.4.1)

# Path to external projects:
# * libpng-android
# * OpenSceneGraph
# * mongoose
# * NLohmann's json
SET(EXT_PROJ_DIR "../../../..")

# Reference libpng-android.
SET(PNG_SOURCE_DIR "${EXT_PROJ_DIR}/libpng-android")
SET(PNG_BUILD_DIR "${PNG_SOURCE_DIR}/build/${ANDROID_ABI}")
# Only build libpng-android if it has not yet been built.
IF (NOT EXISTS "${PNG_BUILD_DIR}/libpng.a")
    FILE(MAKE_DIRECTORY ${PNG_BUILD_DIR})
    ADD_SUBDIRECTORY(${PNG_SOURCE_DIR} ${PNG_BUILD_DIR})
ENDIF ()
# Reference libpng-android includes.
INCLUDE_DIRECTORIES(${PNG_SOURCE_DIR}/jni)
# Reference libpng-android libraries.
LINK_DIRECTORIES(${PNG_BUILD_DIR})
# Force PNG specific flags for OSG.
SET(PNG_FOUND ON CACHE BOOL "PNG is found")
SET(OSG_CPP_EXCEPTIONS_AVAILABLE ON CACHE BOOL "Enable exceptions to build PNG")
SET(PNG_INCLUDE_DIR ${PNG_SOURCE_DIR}/jni)

# Specify critical OpenSceneGraph build variables.
SET(OPENGL_PROFILE "GLES2" CACHE STRING "OpenGL variant to use")
SET(DYNAMIC_OPENTHREADS OFF CACHE BOOL "Link OpenThreads statically")
SET(DYNAMIC_OPENSCENEGRAPH OFF CACHE BOOL "Link OpenSceneGraph statically")
# Reference OpenSceneGraph.
SET(OSG_SOURCE_DIR "${EXT_PROJ_DIR}/OpenSceneGraph")
SET(OSG_BUILD_DIR "${OSG_SOURCE_DIR}/build/Android-${ANDROID_ABI}")
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

# Reference Mongoose HTTP client library.
INCLUDE_DIRECTORIES(${EXT_PROJ_DIR}/mongoose)
ADD_LIBRARY(network-extlib STATIC src/main/cpp/network-extlib.cpp)

# Reference NLohmann's JSON parsing library.
INCLUDE_DIRECTORIES(${EXT_PROJ_DIR}/json/single_include)

# Reference source headers.
INCLUDE_DIRECTORIES(src/main/cpp)
# Reference resource headers.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../../../data)

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
    osgdb_png
    png
    osgdb_osg
    osgdb_serializers_osg
    # osgDB plugins end.
    osgGA
    osgShadow
    osgText
    osgUtil
    osg
    OpenThreads
    network-extlib
)

