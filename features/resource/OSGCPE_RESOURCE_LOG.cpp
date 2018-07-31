FEATURE resource.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_RESOURCE_LOG_PREFIX "resource %s"
#define OSGCPE_RESOURCE_LOG(...) \
    log::logprintf( \
        OSGCPE_RESOURCE_LOG_PREFIX, \
        format::printfString(__VA_ARGS__).c_str() \
    )

