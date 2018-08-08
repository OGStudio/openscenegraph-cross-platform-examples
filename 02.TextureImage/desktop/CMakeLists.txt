CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../openscenegraph-cross-platform-examples")

# Include common CMakeLists.txt.
INCLUDE(${CMAKE_SOURCE_DIR}/../CMakeLists.txt)

# Reference sources.
INCLUDE_DIRECTORIES(src)
# Create executable.
ADD_EXECUTABLE(ex02-texture-image src/main.cpp)

# Use ImageIO instead PNG for macOS.
IF (${OSG_PLATFORM} STREQUAL "macos")
    SET(OSGCPE_IMAGE_LINK_LIBS "osgdb_imageio")
ENDIF ()

# Link executable with libraries.
TARGET_LINK_LIBRARIES(
    ex02-texture-image
    ${OSGCPE_LINK_LIBS}
    ${OSGCPE_IMAGE_LINK_LIBS}
)
