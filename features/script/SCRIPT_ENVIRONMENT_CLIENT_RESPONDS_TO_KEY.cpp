FEATURE script.h/Impl
#define SCRIPT_ENVIRONMENT_CLIENT_RESPONDS_TO_KEY(...) \
    [=](const std::string &key) { \
        __VA_ARGS__ \
    }
