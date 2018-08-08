CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../../openscenegraph-cross-platform-examples")

# Include common CMakeLists.txt.
INCLUDE(${CMAKE_SOURCE_DIR}/../../CMakeLists.txt)

# Reference sources.
INCLUDE_DIRECTORIES(src/main/cpp)
# Create native library.
ADD_LIBRARY(library SHARED src/main/cpp/library.cpp)

FIND_LIBRARY(log-lib log)

# Link native library with libraries.
TARGET_LINK_LIBRARIES(
    library
    ${log-lib}
    ${OSGCPE_LINK_LIBS}
)
