PROJECT(EX02_TEXTURE_IMAGE)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Build OpenSceneGraph statically.
INCLUDE(../../libs/OpenSceneGraph/CMakeLists.txt)

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Reference source headers.
INCLUDE_DIRECTORIES(src)
# Reference resource headers.
INCLUDE_DIRECTORIES(../../data)
# Create executable.
ADD_EXECUTABLE(ex02-texture-image src/main.cpp)
# Link executable with libraries.
TARGET_LINK_LIBRARIES(
    ex02-texture-image
    osgViewer
    osgUtil
    osgDB
    osgdb_osg
    osgdb_serializers_osg
    osgdb_png
    png
    osgGA
    osg
    OpenThreads
)
