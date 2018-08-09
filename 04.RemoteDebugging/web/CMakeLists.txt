PROJECT(EX04_REMOTE_DEBUGGING)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../openscenegraph-cross-platform-examples")

# Include common CMakeLists.txt.
INCLUDE(${CMAKE_SOURCE_DIR}/../CMakeLists.txt)
# Reference NLohmann's JSON parsing library.
INCLUDE_DIRECTORIES(${OSGCPE_DIR}/../json/single_include)

# Reference sources.
INCLUDE_DIRECTORIES(src)
# Create executable (aka HTML page).
ADD_EXECUTABLE(${EXAMPLE_BINARY_NAME} src/main.cpp)

SET(IMAGE_LINK_LIBS "osgdb_png")

# Link executable with libraries.
TARGET_LINK_LIBRARIES(
    ${EXAMPLE_BINARY_NAME}
    ${OSGCPE_LINK_LIBS}
    ${IMAGE_LINK_LIBS}
)

# Set special build flags:
# * -O3: make compact binary, critical for web
# * -s USE_SDL=2: provide SDL2
# * -s ALLOW_MEMORY_GROWTH=1: allow total memory used to increase when necessary
# * -s USE_LIBPNG=1: use libpng
# * -s USE_ZLIB=1: use zlib, necessary for libpng
# * -s FETCH=1: use FetchAPI for HTTP(s) requests
# * -s WASM=0: disable WebAssembly because FetchAPI is unsupported there yet
SET(BUILD_FLAGS "-O3 -s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1 -s USE_LIBPNG=1 -s USE_ZLIB=1 -s FETCH=1 -s WASM=0")
ADD_DEFINITIONS(${BUILD_FLAGS})

# Make Emscripten generate ready-to-open HTML page.
SET(CMAKE_EXECUTABLE_SUFFIX ".html")
# Link with special build flags.
SET_TARGET_PROPERTIES(${EXAMPLE_BINARY_NAME} PROPERTIES LINK_FLAGS ${BUILD_FLAGS})
