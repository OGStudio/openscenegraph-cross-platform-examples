FEATURE network.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_NETWORK_HTTP_CLIENT_LOG_PREFIX "osgcpe::network::HTTPClient(%p) %s"
#define OSGCPE_NETWORK_HTTP_CLIENT_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_NETWORK_HTTP_CLIENT_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )
