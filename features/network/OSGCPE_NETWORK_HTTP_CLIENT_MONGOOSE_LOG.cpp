FEATURE network.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_NETWORK_HTTP_CLIENT_MONGOOSE_LOG_PREFIX "osgcpe::network::HTTPClientMongoose(%p) %s"
#define OSGCPE_NETWORK_HTTP_CLIENT_MONGOOSE_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_NETWORK_HTTP_CLIENT_MONGOOSE_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )
