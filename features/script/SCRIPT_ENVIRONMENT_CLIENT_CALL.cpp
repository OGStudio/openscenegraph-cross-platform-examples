FEATURE script.h/Impl
#define SCRIPT_ENVIRONMENT_CLIENT_CALL(...) \
    [=](const std::string &key, const script::EnvironmentClient::Values &values) { \
        __VA_ARGS__ \
    }
