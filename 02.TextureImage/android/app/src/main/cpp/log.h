
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

// log-android Start
#include <android/log.h>

// log-android End
// logLevelToString Start
#include <osg/Notify>

// logLevelToString End
// logprintf Start
#include <cstdarg>

// logprintf End

namespace osgcpe
{
namespace log
{

// log-android Start
//! Cross-platform logging function.
void log(const char *message)
{
    __android_log_write(ANDROID_LOG_ERROR, "OSG", message);
}
// log-android End
// logLevelToString Start
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
// logLevelToString End
// logprintf Start
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
// logprintf End

// Logger Start
//! Print OpenSceneGraph notifications to console.
class Logger : public osg::NotifyHandler
{
    public:
        Logger(const std::string &domain = "") : domain(domain) { }
        virtual ~Logger() { }

        // Override NotifyHandler::notify() to receive OpenSceneGraph notifications.
        void notify(osg::NotifySeverity severity, const char *message) override
        {
            logprintf(
                "%s OSG/%s %s",
                domain.c_str(),
                logLevelToString(severity).c_str(),
                message
            );
        }

    private:
        const std::string domain;
};
// Logger End

} // namespace log
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_LOG_H

