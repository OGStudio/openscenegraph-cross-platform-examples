FEATURE core.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_CORE_REPORTER_LOG_PREFIX "osgcpe::core::Reporter(%p) %s"
#define OSGCPE_CORE_REPORTER_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_CORE_REPORTER_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )

