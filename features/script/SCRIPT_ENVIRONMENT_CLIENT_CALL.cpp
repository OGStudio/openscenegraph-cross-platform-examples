FEATURE script.h/Impl
#define SCRIPT_ENVIRONMENT_CLIENT_CALL(...) \
    [=](const std::string &key, const std::vector<std::string> &values) { \
        __VA_ARGS__ \
    }
