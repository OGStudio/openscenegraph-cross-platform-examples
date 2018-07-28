FEATURE core.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_APPLICATION_LOG_PREFIX "osgcpe::Application(%p) %s"
#define OSGCPE_APPLICATION_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_APPLICATION_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )

