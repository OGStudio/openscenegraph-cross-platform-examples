FEATURE core.h/Impl
#include "log.h"
#include "format.h"
#define CORE_SEQUENCE_LOG_PREFIX "core::Sequence(%p) %s"
#define CORE_SEQUENCE_LOG(...) \
    log::logprintf( \
        CORE_SEQUENCE_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )

