FEATURE library.cpp/Impl
#include "log.h"
#define OSGCPE_LIBRARY_LOG_PREFIX "osgcpe-library %s"
#define OSGCPE_LIBRARY_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_LIBRARY_LOG_PREFIX, \
        osgcpe::log::printfString(__VA_ARGS__).c_str() \
    )

