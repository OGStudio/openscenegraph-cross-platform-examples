FEATURE core.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_CORE_SEQUENCE_LOG_PREFIX "core::Sequence(%p) %s"
#define OSGCPE_CORE_SEQUENCE_LOG(...) \
    log::logprintf( \
        OSGCPE_CORE_SEQUENCE_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )

