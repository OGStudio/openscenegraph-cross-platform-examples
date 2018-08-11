PROJECT(STATIC_OPENSCENEGRAPH)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Build OpenSceneGraph into static library.

# Detect platform.
SET(OSG_PLATFORM "linux")
# macOS.
IF (APPLE)
    SET(OSG_PLATFORM "macos")
# Web.
ELSEIF (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    SET(OSG_PLATFORM "web")
# Android.
ELSEIF (${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    SET(OSG_PLATFORM "android")
ENDIF ()
# TODO Windows.
MESSAGE("OSG_PLATFORM: '${OSG_PLATFORM}'")

# Path to openscenegraph-cross-platform-examples.
SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../openscenegraph-cross-platform-examples")
# Use different path for Android.
IF (${OSG_PLATFORM} STREQUAL "android")
    SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../../openscenegraph-cross-platform-examples")
ENDIF ()
# Path to OpenSceneGraph source.
SET(OSG_SRC_DIR "${OSGCPE_DIR}/../OpenSceneGraph")
# Path to this directory with our OpenSceneGraph files.
SET(OSG "${OSGCPE_DIR}/libs/OpenSceneGraph")

# Include cross-platform headers.
INCLUDE_DIRECTORIES(${OSG_SRC_DIR})
INCLUDE_DIRECTORIES(${OSG_SRC_DIR}/include)

# Include platform specific headers.
IF (${OSG_PLATFORM} STREQUAL "linux")
    INCLUDE_DIRECTORIES(${OSG}/include/linux)
ELSEIF (${OSG_PLATFORM} STREQUAL "web")
    INCLUDE_DIRECTORIES(${OSG}/include/web)
ELSEIF (${OSG_PLATFORM} STREQUAL "macos")
    INCLUDE_DIRECTORIES(${OSG}/include/macos)
ELSEIF (${OSG_PLATFORM} STREQUAL "android")
    INCLUDE_DIRECTORIES(${OSG}/include/android)
ENDIF ()
# TODO Windows.

# Libraries.
SET(SRC "${OSG}/src")

# OpenThreads.
SET(THREADS_PLATFORM_LIBS "pthread")
# Android already provides "pthread", no need to specify it.
IF (${OSG_PLATFORM} STREQUAL "android")
    SET(THREADS_PLATFORM_LIBS "")
ENDIF ()
ADD_LIBRARY(OpenThreads STATIC ${SRC}/OpenThreads.cpp)
TARGET_LINK_LIBRARIES(OpenThreads ${THREADS_PLATFORM_LIBS})

# osg.
ADD_LIBRARY(
    osg
    STATIC
    ${SRC}/osg-01.cpp
    ${SRC}/osg-02.cpp
    ${SRC}/osg-03.cpp
)

# osgDB.
SET(DB_PLATFORM_LIBS "")
SET(DB_SRC "${SRC}/osgDB.cpp")
IF (${OSG_PLATFORM} STREQUAL "linux")
    SET(DB_PLATFORM_LIBS "dl")
ELSEIF (${OSG_PLATFORM} STREQUAL "macos")
    SET(DB_SRC "${SRC}/osgDB.mm")
ELSEIF (${OSG_PLATFORM} STREQUAL "android")
    SET(DB_PLATFORM_LIBS "z")
ENDIF ()
ADD_LIBRARY(osgDB STATIC ${DB_SRC})
TARGET_LINK_LIBRARIES(osgDB ${DB_PLATFORM_LIBS})

# osgGA.
ADD_LIBRARY(osgGA STATIC ${SRC}/osgGA.cpp)

# osgUtil.
ADD_LIBRARY(osgUtil STATIC ${SRC}/osgUtil.cpp)

# osgViewer.
SET(VIEWER_PLATFORM_SRC "")
SET(VIEWER_PLATFORM_LIBS "")
IF (${OSG_PLATFORM} STREQUAL "linux")
    SET(VIEWER_PLATFORM_SRC ${SRC}/osgViewer-linux.cpp)
    SET(VIEWER_PLATFORM_LIBS "GL" "X11")
ELSEIF (${OSG_PLATFORM} STREQUAL "macos")
    SET(VIEWER_PLATFORM_SRC ${SRC}/osgViewer-macos.mm)
    SET(
        VIEWER_PLATFORM_LIBS
        "-framework Accelerate"
        "-framework Foundation"
        "-framework Cocoa"
        "-framework ImageIO"
        "-framework OpenGL"
    )
ELSEIF (${OSG_PLATFORM} STREQUAL "web")
    SET(VIEWER_PLATFORM_SRC ${SRC}/osgViewer.cpp)
    SET(VIEWER_PLATFORM_LIBS "EGL")
ELSEIF (${OSG_PLATFORM} STREQUAL "android")
    SET(VIEWER_PLATFORM_SRC ${SRC}/osgViewer.cpp)
    SET(VIEWER_PLATFORM_LIBS "GLESv2")
ENDIF ()
ADD_LIBRARY(osgViewer STATIC ${VIEWER_PLATFORM_SRC})
TARGET_LINK_LIBRARIES(osgViewer ${VIEWER_PLATFORM_LIBS})

# osgt plugin.
ADD_LIBRARY(osgdb_osg STATIC ${SRC}/osgdb_osg.cpp)

# ImageIO plugin for macOS.
IF (${OSG_PLATFORM} STREQUAL "macos")
    ADD_LIBRARY(osgdb_imageio STATIC ${SRC}/osgdb_imageio.cpp)
# PNG plugin for other platforms.
ELSE ()
    ADD_LIBRARY(osgdb_png STATIC ${SRC}/osgdb_png.cpp)
ENDIF ()

ADD_LIBRARY(
    osgdb_serializers_osg
    ${SRC}/osgdb_serializers_osg-LibraryWrapper.cpp
    ${SRC}/osgdb_serializers_osg-Drawable.cpp
    ${SRC}/osgdb_serializers_osg-Geode.cpp
    ${SRC}/osgdb_serializers_osg-Geometry.cpp
    ${SRC}/osgdb_serializers_osg-Group.cpp
    ${SRC}/osgdb_serializers_osg-MatrixTransform.cpp
    ${SRC}/osgdb_serializers_osg-Node.cpp
    ${SRC}/osgdb_serializers_osg-Object.cpp
    ${SRC}/osgdb_serializers_osg-Transform.cpp
)
