FEATURE debug.h/Impl
#include "log.h"
#include "format.h"
#define DEBUG_PAGE_LOG_PREFIX "debug::Page(%p) %s"
#define DEBUG_PAGE_LOG(...) \
    log::logprintf( \
        DEBUG_PAGE_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )

