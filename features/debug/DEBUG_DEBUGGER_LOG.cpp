FEATURE debug.h/Impl
#include "log.h"
#include "format.h"
#define DEBUG_DEBUGGER_LOG_PREFIX "debug::Debugger(%p) %s"
#define DEBUG_DEBUGGER_LOG(...) \
    log::logprintf( \
        DEBUG_DEBUGGER_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
