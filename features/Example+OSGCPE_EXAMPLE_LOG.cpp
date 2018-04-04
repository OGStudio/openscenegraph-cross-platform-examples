FEATURE Example.h/Impl
#include "log.h"
#define OSGCPE_EXAMPLE_LOG_PREFIX "osgcpe-example(%p) %s"
#define OSGCPE_EXAMPLE_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_EXAMPLE_LOG_PREFIX, \
        this, \
        osgcpe::log::printfString(__VA_ARGS__).c_str() \
    )

