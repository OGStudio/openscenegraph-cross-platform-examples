PROJECT(STATIC_LUA)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Build Lua into static library.

# Path to Lua source.
SET(LUA_SRC_DIR "${OSGCPE_DIR}/../lua/src")
# Path to this directory with our Lua files.
SET(LUA "${OSGCPE_DIR}/libs/lua")

# Reference Lua.
INCLUDE_DIRECTORIES(${LUA_SRC_DIR})
ADD_LIBRARY(lua STATIC ${LUA}/lua.c)

#TARGET_LINK_LIBRARIES(
#    mongoose
#    ssl
#    crypto
#)

# Reference OpenSSL.
#SET(OPENSSL_INC_DIR "" CACHE PATH "Path to OpenSSL include directory")
#SET(OPENSSL_LIB_DIR "" CACHE PATH "Path to OpenSSL lib directory")
#INCLUDE_DIRECTORIES(${OPENSSL_INC_DIR})
#LINK_DIRECTORIES(${OPENSSL_LIB_DIR})
## Use SSL.
#ADD_DEFINITIONS("-DMG_ENABLE_SSL=1")

