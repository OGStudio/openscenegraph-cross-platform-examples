FEATURE core.h/Impl
#include "log.h"
#include "format.h"
#define CORE_REPORTER_LOG_PREFIX "core::Reporter(%p) %s"
#define CORE_REPORTER_LOG(...) \
    log::logprintf( \
        CORE_REPORTER_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )

