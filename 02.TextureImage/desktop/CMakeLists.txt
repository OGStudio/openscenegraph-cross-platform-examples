PROJECT(EX02_TEXTURE_IMAGE)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../openscenegraph-cross-platform-examples")

# Build OpenSceneGraph statically.
INCLUDE(${OSGCPE_DIR}/libs/OpenSceneGraph/CMakeLists.txt)

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Reference source headers.
INCLUDE_DIRECTORIES(src)
# Reference resource headers.
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/data)
# Create executable.
ADD_EXECUTABLE(ex02-texture-image src/main.cpp)
# Link executable with libraries.
TARGET_LINK_LIBRARIES(
    ex02-texture-image
    osgViewer
    osgUtil
    osgDB
    # osgDB plugins start.
    osgdb_osg
    osgdb_serializers_osg
    osgdb_png
    png
    # osgDB plugins end.
    osgGA
    osg
    OpenThreads
)
