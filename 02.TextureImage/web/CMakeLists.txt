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
# Create executable (aka HTML page).
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
    # osgDB plugins end.
    osgGA
    osg
    OpenThreads
)

# Set special build flags:
# * -O3: make compact binary, critical for web
# * -s USE_SDL=2: provide SDL2
# * -s ALLOW_MEMORY_GROWTH=1: allow total memory used to increase when necessary
# * -s USE_LIBPNG=1: use libpng
# * -s USE_ZLIB=1: use zlib, necessary for libpng
SET(BUILD_FLAGS "-O3 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -s USE_LIBPNG=1 -s USE_ZLIB=1")
ADD_DEFINITIONS(${BUILD_FLAGS})

# Make Emscripten generate ready-to-open HTML page.
SET(CMAKE_EXECUTABLE_SUFFIX ".html")
# Link with special build flags.
SET_TARGET_PROPERTIES(ex02-texture-image PROPERTIES LINK_FLAGS ${BUILD_FLAGS})
