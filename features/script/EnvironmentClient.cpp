FEATURE script.h/Include
#include <functional>

FEATURE script.h/Impl
//! Serve as an interface to scriptable entity.
class EnvironmentClient
{
    public:
        typedef std::vector<std::string> Values;

        EnvironmentClient() :
            respondsToKey(nullptr),
            call(nullptr)
        { }
        ~EnvironmentClient() { }

        // 'respondsToKey' method/callback.
        typedef std::function<bool (const std::string &)> CallbackRespondsToKey;
        CallbackRespondsToKey respondsToKey;

        // 'call' method/callback.
        typedef std::function<Values (const std::string &, const Values &)> CallbackCall;
        CallbackCall call;
};
