FEATURE Logger.h/Impl
#include <android/log.h>

// Log message using platform specific tools.
void platformLog(const char *message)
{
    __android_log_write(ANDROID_LOG_ERROR, "OSG", message);
}

