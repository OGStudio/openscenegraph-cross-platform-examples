# NOTE This is a common CMakeLists.txt to be included by each platform's
# NOTE specific CMakeLists.txt.
# This CMakeLists.txt requires the following variables:
# * OSGCPE_DIR
# This CMakeLists.txt provides the following variables outside:
# * EXAMPLE_BINARY_NAME
# * OSGCPE_LINK_LIBS

PROJECT(EX06_COMMAND_SEQUENCE)
SET(EXAMPLE_BINARY_NAME "ex06-command-sequence")

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Build OpenSceneGraph statically.
INCLUDE(${OSGCPE_DIR}/libs/OpenSceneGraph/CMakeLists.txt)

# Reference resources.
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/data)

# Provide libraries to link with.
SET(
    OSGCPE_LINK_LIBS
    osgViewer
    osgUtil
    osgDB
    # osgDB plugins start.
    osgdb_osg
    osgdb_serializers_osg
    # osgDB plugins end.
    osgGA
    osg
    OpenThreads
)
