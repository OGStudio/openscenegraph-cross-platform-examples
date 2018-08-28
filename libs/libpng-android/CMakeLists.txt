PROJECT(STATIC_LIBPNG_ANDROID)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Build libpng-android into static library under Android.

# NOTE Must be provided by parent.
#SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../../openscenegraph-cross-platform-examples")

# Path to libpng-android source.
SET(PNG_SRC_DIR "${OSGCPE_DIR}/../libpng-android/jni")
INCLUDE_DIRECTORIES(${PNG_SRC_DIR})
# Path to this directory with our libpng-android files.
SET(PNG_DIR "${OSGCPE_DIR}/libs/libpng-android")

# Libraries.
SET(SRC "${PNG_DIR}/src")

ADD_LIBRARY(
    png
    STATIC
    ${SRC}/libpng.cpp
    ${PNG_SRC_DIR}/arm/filter_neon.S
)
TARGET_LINK_LIBRARIES(png z)
