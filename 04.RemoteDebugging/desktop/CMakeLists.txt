PROJECT(EX04_REMOTE_DEBUGGING)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../..")

# Build OpenSceneGraph statically.
INCLUDE(../../libs/OpenSceneGraph/CMakeLists.txt)
# Build mongoose statically.
INCLUDE(../../libs/mongoose/CMakeLists.txt)
# Reference NLohmann's JSON parsing library.
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/../json/single_include)

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Reference source headers.
INCLUDE_DIRECTORIES(src)
# Reference resource headers.
INCLUDE_DIRECTORIES(../../data)
# Create executable.
ADD_EXECUTABLE(ex04-remote-debugging src/main.cpp)
# Link executable with OpenSceneGraph libraries.
TARGET_LINK_LIBRARIES(
    ex04-remote-debugging
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
    mongoose
)
