FEATURE input.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_INPUT_MOUSE_LOG_PREFIX "osgcpe::input::Mouse(%p) %s"
#define OSGCPE_INPUT_MOUSE_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_INPUT_MOUSE_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )
