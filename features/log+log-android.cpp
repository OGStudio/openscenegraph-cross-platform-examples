FEATURE log.h/Include
#include <android/log.h>

FEATURE log.h/Impl
//! Cross-platform logging function.
void log(const char *message)
{
    __android_log_write(ANDROID_LOG_ERROR, "OSG", message);
}
