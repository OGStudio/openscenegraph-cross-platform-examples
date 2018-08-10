PROJECT(EX04_REMOTE_DEBUGGING)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../openscenegraph-cross-platform-examples")

# Include common CMakeLists.txt.
INCLUDE(${CMAKE_SOURCE_DIR}/../CMakeLists.txt)

# Build mongoose statically.
INCLUDE(${OSGCPE_DIR}/libs/mongoose/CMakeLists.txt)
# Reference NLohmann's JSON parsing library.
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/../json/single_include)

# Reference sources.
INCLUDE_DIRECTORIES(src)
# Create executable.
ADD_EXECUTABLE(${EXAMPLE_BINARY_NAME} src/main.cpp)

# Use ImageIO for macOS.
IF (${OSG_PLATFORM} STREQUAL "macos")
    SET(IMAGE_LINK_LIBS "osgdb_imageio")
# Use libpng for Linux and Windows.
ELSE ()
    SET(IMAGE_LINK_LIBS "osgdb_png" "png")
ENDIF ()

# Link executable with libraries.
TARGET_LINK_LIBRARIES(
    ${EXAMPLE_BINARY_NAME}
    ${OSGCPE_LINK_LIBS}
    ${IMAGE_LINK_LIBS}
    mongoose
)
