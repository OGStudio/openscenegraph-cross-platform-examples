FEATURE Application.h/Include
#include "Logger.h"

FEATURE Application.h/Setup
this->setupLogging();

FEATURE Application.h/TearDown
this->tearLoggingDown();

FEATURE Application.h/Impl
private:
    Logger *logger;
    void setupLogging()
    {
        // Create custom logger.
        this->logger = new Logger;
        // Provide the logger to OpenSceneGraph.
        osg::setNotifyHandler(this->logger);
        // Only accept notifications of Info level or higher
        // like warnings and errors.
        osg::setNotifyLevel(osg::INFO);
    }
    void tearLoggingDown()
    {
        // Remove the logger from OpenSceneGraph.
        // This also destroys the logger: no need to deallocate it manually.
        osg::setNotifyHandler(0);
    }
