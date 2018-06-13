FEATURE resource.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_RESOURCE_LOG_PREFIX "osgcpe::resource %s"
#define OSGCPE_RESOURCE_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_RESOURCE_LOG_PREFIX, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )

