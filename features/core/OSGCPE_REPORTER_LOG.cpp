FEATURE core.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_REPORTER_LOG_PREFIX "osgcpe::Reporter(%p) %s"
#define OSGCPE_REPORTER_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_REPORTER_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )

