FEATURE main.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_MAIN_APPLICATION_LOG_PREFIX "main::Application(%p) %s"
#define OSGCPE_MAIN_APPLICATION_LOG(...) \
    log::logprintf( \
        OSGCPE_MAIN_APPLICATION_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
