FEATURE Debugger.h/Impl
#include "log.h"
#define OSGCPE_DEBUGGER_LOG_PREFIX "osgcpe-Debugger(%p) %s"
#define OSGCPE_DEBUGGER_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_DEBUGGER_LOG_PREFIX, \
        this, \
        osgcpe::log::printfString(__VA_ARGS__).c_str() \
    )

