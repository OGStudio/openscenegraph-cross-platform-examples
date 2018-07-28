PROJECT(EX05_NODE_SELECTION)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# OpenSceneGraph directories.
SET(OSG_INC_DIR "" CACHE PATH "Path to OpenSceneGraph include directory")
SET(OSG_LIB_DIR "" CACHE PATH "Path to OpenSceneGraph lib directory")
INCLUDE_DIRECTORIES(${OSG_INC_DIR})
LINK_DIRECTORIES(${OSG_LIB_DIR})

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
    osgDB
    osgGA
    osgUtil
    osg
    OpenThreads
)
