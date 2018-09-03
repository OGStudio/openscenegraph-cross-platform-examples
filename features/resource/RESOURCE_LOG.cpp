FEATURE resource.h/Impl
#include "log.h"
#include "format.h"
#define RESOURCE_LOG_PREFIX "resource %s"
#define RESOURCE_LOG(...) \
    log::logprintf( \
        RESOURCE_LOG_PREFIX, \
        format::printfString(__VA_ARGS__).c_str() \
    )

