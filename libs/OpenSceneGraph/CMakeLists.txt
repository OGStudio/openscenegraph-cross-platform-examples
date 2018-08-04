# Build OpenSceneGraph into static library.

# TODO: Provide flag to set iOS sim/dev.
# Detect platform.
SET(OSG_PLATFORM "Linux")
# macOS.
IF (APPLE)
    SET(OSG_PLATFORM "macOS")
ENDIF ()
# TODO Web.
# TODO Android.
# TODO iOS.
# TODO Windows.


# Path to OpenSceneGraph source.
SET(OSG_SRC_DIR "${CMAKE_SOURCE_DIR}/../../../OpenSceneGraph")

# Include cross-platform headers.
INCLUDE_DIRECTORIES(${OSG_SRC_DIR})
INCLUDE_DIRECTORIES(${OSG_SRC_DIR}/include)

# Include platform specific headers.
IF (OSG_PLATFORM EQUAL "Linux")
    INCLUDE_DIRECTORIES(include/linux)
ELSEIF (OSG_PLATFORM EQUAL "macOS")
    INCLUDE_DIRECTORIES(include/macos)
ENDIF ()
# TODO Windows.
# TODO iOS.
# TODO Android.
# TODO Web.

# Libraries.
ADD_LIBRARY(OpenThreads STATIC src/OpenThreads.cpp)
ADD_LIBRARY(
    osg
    STATIC
    src/osg-01.cpp
    src/osg-02.cpp
    src/osg-03.cpp
)
ADD_LIBRARY(osgDB STATIC src/osgDB.cpp)
ADD_LIBRARY(osgGA STATIC src/osgGA.cpp)
ADD_LIBRARY(osgUtil STATIC src/osgUtil.cpp)

# osgViewer.
SET(VIEWER_PLATFORM_SRC "")
SET(VIEWER_PLATFORM_LIBS "")
IF (OSG_PLATFORM EQUAL "Linux")
    SET(VIEWER_PLATFORM_SRC src/osgViewer-Linux.cpp)
    SET(VIEWER_PLATFORM_LIBS "X11")
ENDIF ()
ADD_LIBRARY(
    osgViewer
    STATIC
    src/osgViewer.cpp
    ${VIEWER_PLATFORM_SRC}
)
TARGET_LINK_LIBRARIES(osgViewer ${VIEWER_PLATFORM_LIBS)

# osgt plugin.
ADD_LIBRARY(osgdb_osg STATIC src/osgdb_osg.cpp)

# TODO Reference OSG SRC DIR files!
#ADD_LIBRARY(
#    osgdb_serializers_osg
#    src/osgdb_serializers_osg-LibraryWrapper.cpp
#    src/osgdb_serializers_osg-Geometry.cpp
#    src/osgdb_serializers_osg-Group.cpp
#    src/osgdb_serializers_osg-MatrixTransform.cpp
#    src/osgdb_serializers_osg-Node.cpp
#    src/osgdb_serializers_osg-Object.cpp
#    src/osgdb_serializers_osg-Transform.cpp
#)
