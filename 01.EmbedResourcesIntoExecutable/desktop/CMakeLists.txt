PROJECT(EXAMPLE_EMBED_RESOURCE)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# OpenSceneGraph directories.
SET(OSG_INC_DIR "" CACHE PATH "Path to OpenSceneGraph include directory")
SET(OSG_LIB_DIR "" CACHE PATH "Path to OpenSceneGraph lib directory")
INCLUDE_DIRECTORIES(${OSG_INC_DIR})
LINK_DIRECTORIES(${OSG_LIB_DIR})

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Reference own includes.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src-gen)
# Create executable.
ADD_EXECUTABLE(exampleEmbedResource src/main.cpp)
# Link executable with OpenSceneGraph libraries.
TARGET_LINK_LIBRARIES(exampleEmbedResource osg osgDB osgGA osgViewer)
