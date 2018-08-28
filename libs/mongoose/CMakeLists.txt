PROJECT(STATIC_MONGOOSE)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Build mongoose into static library.

# Path to openscenegraph-cross-platform-examples.
# NOTE Must by provided by parent.
#SET(OSGCPE_DIR "${CMAKE_SOURCE_DIR}/../../../openscenegraph-cross-platform-examples")

# Path to mongoose source.
SET(MONGOOSE_SRC_DIR "${OSGCPE_DIR}/../mongoose")
# Path to this directory with our mongoose files.
SET(MONGOOSE "${OSGCPE_DIR}/libs/mongoose")

# Reference mongoose.
INCLUDE_DIRECTORIES(${MONGOOSE_SRC_DIR})
ADD_LIBRARY(mongoose STATIC ${MONGOOSE}/mongoose.cpp)
TARGET_LINK_LIBRARIES(
    mongoose
    ssl
    crypto
)

# Reference OpenSSL.
SET(OPENSSL_INC_DIR "" CACHE PATH "Path to OpenSSL include directory")
SET(OPENSSL_LIB_DIR "" CACHE PATH "Path to OpenSSL lib directory")
INCLUDE_DIRECTORIES(${OPENSSL_INC_DIR})
LINK_DIRECTORIES(${OPENSSL_LIB_DIR})
# Use SSL.
ADD_DEFINITIONS("-DMG_ENABLE_SSL=1")

