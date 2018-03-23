FEATURE main.cpp/Impl
#include "log.h"
#define OSGCPE_MAIN_LOG_PREFIX "osgcpe-main %s"
#define OSGCPE_MAIN_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_MAIN_LOG_PREFIX, \
        osgcpe::log::printfString(__VA_ARGS__).c_str() \
    )

