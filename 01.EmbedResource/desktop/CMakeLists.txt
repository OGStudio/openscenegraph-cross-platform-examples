PROJECT(EX01_EMBED_RESOURCE)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Path to external projects:
# * OpenSceneGraph
SET(EXT_PROJ_DIR "${CMAKE_SOURCE_DIR}/../../..")

# Create custom OpenSceneGraph static libraries.
INCLUDE_DIRECTORIES(${EXT_PROJ_DIR}/OpenSceneGraph)
INCLUDE_DIRECTORIES(${EXT_PROJ_DIR}/OpenSceneGraph/include)
ADD_LIBRARY(openthreads STATIC src/openthreads.cpp)
ADD_LIBRARY(openscenegraph01 STATIC src/openscenegraph01.cpp)
ADD_LIBRARY(openscenegraph02 STATIC src/openscenegraph02.cpp)
ADD_LIBRARY(openscenegraph03 STATIC src/openscenegraph03.cpp)
ADD_LIBRARY(openscenegraphDB STATIC src/openscenegraphDB.cpp)
ADD_LIBRARY(openscenegraphGA STATIC src/openscenegraphGA.cpp)
ADD_LIBRARY(openscenegraphUtil STATIC src/openscenegraphUtil.cpp)
ADD_LIBRARY(openscenegraphViewer STATIC src/openscenegraphViewer.cpp)

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Reference source headers.
INCLUDE_DIRECTORIES(src)
# Reference resource headers.
INCLUDE_DIRECTORIES(../../data)
# Create executable.
ADD_EXECUTABLE(ex01-embed-resource src/main.cpp)


SET(PLATFORM_LIBS "X11")

IF (APPLE)
    SET(PLATFORM_LIBS "")
ENDIF ()

# Link executable with OpenSceneGraph libraries.
TARGET_LINK_LIBRARIES(
    ex01-embed-resource
    openscenegraphViewer
    openscenegraphUtil
    openscenegraphDB
    openscenegraphGA
    openscenegraph01
    openscenegraph02
    openscenegraph03
    openthreads
    dl
    pthread
    GL
    ${PLATFORM_LIBS}
)
