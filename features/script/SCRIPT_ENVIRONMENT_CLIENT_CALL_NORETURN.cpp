FEATURE script.h/Impl
#define SCRIPT_ENVIRONMENT_CLIENT_CALL_NORETURN(...) \
    [=](const std::string &key, const script::EnvironmentClient::Values &values) { \
        __VA_ARGS__; \
        script::EnvironmentClient::Values empty; \
        return empty; \
    }
