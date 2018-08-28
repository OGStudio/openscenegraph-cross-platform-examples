PROJECT(JSON_ANDROID)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Provide Android with missing STL functions.

# NOTE Must be provided by parent.
#SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../../openscenegraph-cross-platform-examples")

# Reference NLohmann's JSON library.
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/../json)
# Provide custom header for inclusion.
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/libs/json-android/include)
