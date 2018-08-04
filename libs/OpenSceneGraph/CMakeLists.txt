PROJECT(STATIC_OPENSCENEGRAPH)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Build OpenSceneGraph into static library.

# TODO: Provide flag to set iOS sim/dev.
# Detect platform.
SET(OSG_PLATFORM "linux")
# macOS.
IF (APPLE)
    SET(OSG_PLATFORM "macos")
# Web.
ELSEIF (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    SET(OSG_PLATFORM "web")
ENDIF ()
# TODO Android.
# TODO iOS.
# TODO Windows.
MESSAGE("OSG_PLATFORM: '${OSG_PLATFORM}'")

# Path to OpenSceneGraph source.
SET(OSG_SRC_DIR "${CMAKE_SOURCE_DIR}/../../../OpenSceneGraph")
# Path to this directory with our OpenSceneGraph files.
SET(OSG "${CMAKE_SOURCE_DIR}/../../libs/OpenSceneGraph")

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
ENDIF ()
# TODO Windows.
# TODO iOS.
# TODO Android.

# Libraries.
SET(SRC "${OSG}/src")

# OpenThreads.
SET(THREADS_PLATFORM_LIBS "pthread")
#IF (${OSG_PLATFORM} STREQUAL "linux")
#    SET(THREADS_PLATFORM_LIBS "pthread")
#ENDIF ()
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
IF (${OSG_PLATFORM} STREQUAL "linux")
    SET(DB_PLATFORM_LIBS "dl")
ENDIF ()
ADD_LIBRARY(osgDB STATIC ${SRC}/osgDB.cpp)
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
ELSEIF (${OSG_PLATFORM} STREQUAL "web")
    SET(VIEWER_PLATFORM_SRC ${SRC}/osgViewer.cpp)
    SET(VIEWER_PLATFORM_LIBS "EGL")
ENDIF ()
ADD_LIBRARY(osgViewer STATIC ${VIEWER_PLATFORM_SRC})
TARGET_LINK_LIBRARIES(osgViewer ${VIEWER_PLATFORM_LIBS})

# osgt plugin.
ADD_LIBRARY(osgdb_osg STATIC ${SRC}/osgdb_osg.cpp)

# png plugin.
ADD_LIBRARY(osgdb_png STATIC ${SRC}/osgdb_png.cpp)

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
