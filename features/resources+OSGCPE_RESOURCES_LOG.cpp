FEATURE resources.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_RESOURCES_LOG_PREFIX "osgcpe-resources %s"
#define OSGCPE_RESOURCES_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_RESOURCES_LOG_PREFIX, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )

