FEATURE resources.h/Impl
#define OSGCPE_RESOURCES_LOG_PREFIX "osgcpe-resources %s"
#define OSGCPE_RESOURCES_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_RESOURCES_LOG_PREFIX, \
        osgcpe::log::printfString(__VA_ARGS__).c_str() \
    )

