FEATURE resource.h/Impl
#include "log.h"
#include "format.h"
#define RESOURCE_POOL_LOG_PREFIX "resource::Pool(%p) %s"
#define RESOURCE_POOL_LOG(...) \
    log::logprintf( \
        RESOURCE_POOL_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
