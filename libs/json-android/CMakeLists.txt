PROJECT(JSON_ANDROID)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Provide Android with missing STL functions.

SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../../openscenegraph-cross-platform-examples")

# Reference NLohmann's JSON library.
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/../json/single_include)
# Path to this directory with our json-android files.
SET(JSON_DIR "${OSGCPE_DIR}/libs/json-android")

ADD_LIBRARY(
    json-android
    STATIC
    ${JSON_DIR}/src/json-android.cpp
)
