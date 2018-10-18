FEATURE script.h/Include
#include <functional>

FEATURE script.h/Impl
//! Serve as an interface to scriptable entity.
class EnvironmentClient
{
    public:
        EnvironmentClient() :
            call(nullptr)
        { }
        ~EnvironmentClient() { }

        // 'call' method/callback.
        typedef
            std::function<
                std::vector<std::string> (
                    const std::string &,
                    const std::vector<std::string> &
                )
            > CallbackCall;
        CallbackCall call;
};
