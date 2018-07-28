FEATURE main.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_MAIN_APPLICATION_LOG_PREFIX "osgcpe::main::Application(%p) %s"
#define OSGCPE_MAIN_APPLICATION_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_MAIN_APPLICATION_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )
