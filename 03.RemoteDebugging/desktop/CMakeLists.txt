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

# Force C++ compiler on Mongoose to work around '-std=c++11',
# which stops building C sources under macOS.
SET(MONGOOSE_SRC ${EXT_PROJ_DIR}/mongoose/mongoose.c)
SET_SOURCE_FILES_PROPERTIES(${MONGOOSE_SRC} PROPERTIES LANGUAGE CXX)
INCLUDE_DIRECTORIES(${EXT_PROJ_DIR}/mongoose)
# Build mongoose statically (for distribution simplicity).
ADD_LIBRARY(mongoose STATIC ${MONGOOSE_SRC})

# Reference NLohmann's json.
INCLUDE_DIRECTORIES(${EXT_PROJ_DIR}/json/single_include)

# Reference source headers.
INCLUDE_DIRECTORIES(
    src
    src/network
)
# Reference resource headers.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../../data)
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
    mongoose
)
