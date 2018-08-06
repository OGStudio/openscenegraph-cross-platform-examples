CMAKE_MINIMUM_REQUIRED(VERSION 3.4.1)

SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../../openscenegraph-cross-platform-examples")

# Build OpenSceneGraph statically.
INCLUDE(${OSGCPE_DIR}/libs/OpenSceneGraph/CMakeLists.txt)


# Reference source headers.
INCLUDE_DIRECTORIES(src/main/cpp)
# Reference resource headers.
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/data)

ADD_LIBRARY(library SHARED src/main/cpp/library.cpp)
FIND_LIBRARY(log-lib log)
# Libraries must be linked in the specified order.
# Otherwise you may get unsatisified linker errors.
TARGET_LINK_LIBRARIES(
    library
    ${log-lib}
    osgViewer
    osgDB
    # osgDB plugins start.
    osgdb_osg
    osgdb_serializers_osg
    # osgDB plugins end.
    osgGA
    osgUtil
    osg
    OpenThreads
)

