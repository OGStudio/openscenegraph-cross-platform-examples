CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../openscenegraph-cross-platform-examples")

# Include common CMakeLists.txt.
INCLUDE(${CMAKE_SOURCE_DIR}/../CMakeLists.txt)

# Reference sources.
INCLUDE_DIRECTORIES(src)
# Create executable.
ADD_EXECUTABLE(${EXAMPLE_BINARY_NAME} src/main.cpp)

# Link executable with libraries.
TARGET_LINK_LIBRARIES(
    ${EXAMPLE_BINARY_NAME}
    ${OSGCPE_LINK_LIBS}
)
