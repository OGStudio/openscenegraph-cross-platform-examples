# NOTE This is a common CMakeLists.txt to be included by each platform's
# NOTE specific CMakeLists.txt.
# This CMakeLists.txt requires the following variables:
# * OSGCPE_DIR
# This CMakeLists.txt provides the following variables outside:
# * EXAMPLE_BINARY_NAME
# * OSGCPE_LINK_LIBS

PROJECT(EX07_LUA_SCRIPTING)
SET(EXAMPLE_BINARY_NAME "ex07-lua-scripting")

# Build OpenSceneGraph statically.
INCLUDE(${OSGCPE_DIR}/libs/OpenSceneGraph/CMakeLists.txt)
# Build Lua statically.
INCLUDE(${OSGCPE_DIR}/libs/lua/CMakeLists.txt)
# Reference Sol2 header-only library.
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/../sol2)


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
