CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../../openscenegraph-cross-platform-examples")

# Include common CMakeLists.txt.
INCLUDE(${CMAKE_SOURCE_DIR}/../../CMakeLists.txt)
# Include libpng-android CMakeLists.txt.
INCLUDE(${OSGCPE_DIR}/libs/libpng-android/CMakeLists.txt)

# Reference Android variant of NLohmann's JSON parsing library.
INCLUDE(${OSGCPE_DIR}/libs/json-android/CMakeLists.txt)

# Reference sources.
INCLUDE_DIRECTORIES(src/main/cpp)
# Create native library.
ADD_LIBRARY(library SHARED src/main/cpp/library.cpp)

FIND_LIBRARY(log-lib log)
SET(IMAGE_LINK_LIBS "osgdb_png" "png")

# Link native library with libraries.
TARGET_LINK_LIBRARIES(
    library
    ${log-lib}
    ${OSGCPE_LINK_LIBS}
    ${IMAGE_LINK_LIBS}
)
