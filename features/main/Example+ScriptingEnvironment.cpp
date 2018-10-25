FEATURE main.h/Include
#include "script.h"
#include <sol.hpp>

FEATURE main.h/Setup
this->setupScriptingEnvironment();

FEATURE main.h/TearDown
this->tearScriptingEnvironmentDown();

FEATURE main.h/Impl
private:
    script::Environment *environment;
    sol::state *lua;

    void setupScriptingEnvironment()
    {
        this->environment = new script::Environment;

        this->lua = new sol::state;
        this->lua->open_libraries();
        // Register Environment instance.
        (*this->lua)["ENV"] = this->environment;
        // Register Environment class.
        this->lua->new_usertype<script::Environment>(
            "Environment",
            // 'setVerbose' method.
            "setVerbose",
            [](script::Environment &env, bool state)
            {
                env.setVerbose(state);
            },
            // 'addClient' method.
            "addClient",
            [](script::Environment &env, script::EnvironmentClient *client, sol::nested<std::vector<std::string> > keys)
            {
                env.addClient(client, keys);
            },
            //&script::Environment::addClient,
            // 'call' method.
            "call",
            [](script::Environment &env, const std::string &key, sol::nested<std::vector<std::string> > values)
            {
                return env.call(key, values);
            }
        );
        // Register EnvironmentClient class.
        this->lua->new_usertype<script::EnvironmentClient>(
            "EnvironmentClient",
            // 'call' method.
            "call",
            sol::property(
                [](script::EnvironmentClient &ec, sol::function luaCallback)
                {
                    ec.call =
                        SCRIPT_ENVIRONMENT_CLIENT_CALL(
                            sol::nested<std::vector<std::string> > result =
                                luaCallback(key, sol::as_table(values));
                            return std::move(result.source);
                        );
                }
            )
        );
    }
    void tearScriptingEnvironmentDown()
    {
        delete this->lua;
        delete this->environment;
    }
