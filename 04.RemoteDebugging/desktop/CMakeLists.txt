PROJECT(EX03_REMOTE_DEBUGGING)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Path to external projects:
# * mongoose
SET(EXT_PROJ_DIR "${CMAKE_SOURCE_DIR}/../../..")

# OpenSceneGraph directories.
SET(OSG_INC_DIR "" CACHE PATH "Path to OpenSceneGraph include directory")
SET(OSG_LIB_DIR "" CACHE PATH "Path to OpenSceneGraph lib directory")
INCLUDE_DIRECTORIES(${OSG_INC_DIR})
LINK_DIRECTORIES(${OSG_LIB_DIR})

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Build mongoose statically (for distribution simplicity).
INCLUDE_DIRECTORIES(${EXT_PROJ_DIR}/mongoose)
ADD_LIBRARY(mongoose STATIC ${EXT_PROJ_DIR}/mongoose/mongoose.c)

# Reference headers.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
# Reference resource headers.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../../data)
# Create executable.
ADD_EXECUTABLE(ex03-remote-debugging src/main.cpp)
# Link executable with OpenSceneGraph libraries.
TARGET_LINK_LIBRARIES(
    ex03-remote-debugging
    osgViewer
    osgDB
    osgGA
    osg
    OpenThreads
    mongoose
)
