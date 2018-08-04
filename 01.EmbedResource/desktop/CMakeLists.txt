PROJECT(EX01_EMBED_RESOURCE)
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
ADD_EXECUTABLE(ex01-embed-resource src/main.cpp)

# Link executable with OpenSceneGraph libraries.
TARGET_LINK_LIBRARIES(
    ex01-embed-resource
    osgViewer
    osgUtil
    osgDB
    osgGA
    osg
    OpenThreads
)
