PROJECT(EX05_NODE_SELECTION)
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
ADD_EXECUTABLE(ex05-node-selection src/main.cpp)
# Link executable with libraries.
TARGET_LINK_LIBRARIES(
    ex05-node-selection
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
