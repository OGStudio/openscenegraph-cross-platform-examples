FEATURE input.h/Impl
#include "log.h"
#include "format.h"
#define INPUT_MOUSE_LOG_PREFIX "input::Mouse(%p) %s"
#define INPUT_MOUSE_LOG(...) \
    log::logprintf( \
        INPUT_MOUSE_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
