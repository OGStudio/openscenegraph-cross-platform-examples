PROJECT(EX03_REMOTE_DEBUGGING)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Path to external projects:
# * mongoose
# * NLohmann's json
SET(EXT_PROJ_DIR "${CMAKE_SOURCE_DIR}/../../..")

# OpenSceneGraph directories.
SET(OSG_INC_DIR "" CACHE PATH "Path to OpenSceneGraph include directory")
SET(OSG_LIB_DIR "" CACHE PATH "Path to OpenSceneGraph lib directory")
INCLUDE_DIRECTORIES(${OSG_INC_DIR})
LINK_DIRECTORIES(${OSG_LIB_DIR})

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Reference OpenSSL (necessary for Mongoose).
SET(OPENSSL_INC_DIR "" CACHE PATH "Path to OpenSSL include directory")
SET(OPENSSL_LIB_DIR "" CACHE PATH "Path to OpenSSL lib directory")
INCLUDE_DIRECTORIES(${OPENSSL_INC_DIR})
LINK_DIRECTORIES(${OPENSSL_LIB_DIR})

# Reference Mongoose HTTP client library.
INCLUDE_DIRECTORIES(${EXT_PROJ_DIR}/mongoose)
ADD_LIBRARY(network-extlib STATIC src/network-extlib.cpp)
TARGET_LINK_LIBRARIES(
    network-extlib
    ssl
    crypto
)

# Reference NLohmann's JSON parsing library.
INCLUDE_DIRECTORIES(${EXT_PROJ_DIR}/json/single_include)

# Reference source headers.
INCLUDE_DIRECTORIES(src)
# Reference resource headers.
INCLUDE_DIRECTORIES(../../data)
# Create executable.
ADD_EXECUTABLE(ex03-remote-debugging src/main.cpp)
# Link executable with OpenSceneGraph libraries.
TARGET_LINK_LIBRARIES(
    ex03-remote-debugging
    osgViewer
    osgDB
    osgGA
    osg
    OpenThreads
    network-extlib
)
