FEATURE log.h/Impl
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
