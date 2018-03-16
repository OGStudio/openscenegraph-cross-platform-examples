FEATURE logging.h/Include
#include <android/log.h>

FEATURE logging.h/Impl
// Log message using platform specific tools.
void platformLog(const char *message)
{
    __android_log_write(ANDROID_LOG_ERROR, "OSG", message);
}

