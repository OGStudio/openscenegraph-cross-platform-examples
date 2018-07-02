FEATURE scene.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_SCENE_LINEAR_INTERPOLATOR_LOG_PREFIX "osgcpe::scene::LinearInterpolator(%p) %s"
#define OSGCPE_SCENE_LINEAR_INTERPOLATOR_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_SCENE_LINEAR_INTERPOLATOR_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )

