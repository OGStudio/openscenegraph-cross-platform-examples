
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_LOG_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_LOG_H

// log+log-android Start
#include <android/log.h>

// log+log-android End
// log+logLevelToString Start
#include <osg/Notify>

// log+logLevelToString End
// log+logprintf Start
#include <cstdarg>

// log+logprintf End

namespace osgcpe
{
namespace log
{

// log+printfString Start
//! Construct a string using printf-like syntax.
std::string printfString(const char *fmt, ...)
{
    const int PRINTF_STRING_MAX_STRLEN = 1024;
    va_list args;
    char msg[PRINTF_STRING_MAX_STRLEN];
    va_start(args, fmt);
    vsnprintf(msg, PRINTF_STRING_MAX_STRLEN, fmt, args);
    va_end(args);
    return msg;
}
// log+printfString End
// log+log-android Start
//! Cross-platform logging function.
void log(const char *message)
{
    __android_log_write(ANDROID_LOG_ERROR, "OSG", message);
}
// log+log-android End
// log+logLevelToString Start
//! Convert OpenSceneGraph log level to string.
std::string logLevelToString(osg::NotifySeverity severity)
{
    switch (severity)
    {
        case osg::DEBUG_FP:
            // Verbose.
            return "V";
        case osg::DEBUG_INFO:
            // Debug.
            return "D";
        case osg::NOTICE:
        case osg::INFO:
            // Info.
            return "I";
        case osg::WARN:
            // Warning.
            return "W";
        case osg::FATAL:
        case osg::ALWAYS:
            // Error.
            return "E";
    }
}
// log+logLevelToString End
// log+logprintf Start
//! Cross-platform logging function with printf-like syntax.
void logprintf(const char *fmt, ...)
{
    const int PRINTF_STRING_MAX_STRLEN = 1024;
    va_list args;
    char msg[PRINTF_STRING_MAX_STRLEN];
    va_start(args, fmt);
    vsnprintf(msg, PRINTF_STRING_MAX_STRLEN, fmt, args);
    va_end(args);
    log(msg);
}
// log+logprintf End

} // namespace log
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_LOG_H

