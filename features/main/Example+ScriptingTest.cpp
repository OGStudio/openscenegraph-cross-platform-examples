FEATURE main.h/Include
#include "script.h"

#include <sol.hpp>

FEATURE main.h/Setup
this->setupScriptingTest();

FEATURE main.h/TearDown
this->tearScriptingTestDown();

FEATURE main.h/Impl
private:
    script::Environment *environment;
    script::EnvironmentClient *sampleClient;
    sol::state *lua;

    void setupScriptingTest()
    {
        this->environment = new script::Environment;
        this->setupSampleClient();

        // Call sample client through Environment interface.
        auto values = this->environment->call("sample", {"A", "B", "C"});
        for (auto value : values)
        {
            MAIN_EXAMPLE_LOG("sample. value: '%s'", value.c_str());
        }

        this->setupLuaEnvironment();
        this->loadCLIScript();
    }
    void tearScriptingTestDown()
    {
        this->tearLuaEnvironmentDown();
        delete this->environment;
        this->tearSampleClientDown();
    }
    void setupSampleClient()
    {
        this->sampleClient = new script::EnvironmentClient;
        this->environment->addClient(this->sampleClient);
        this->sampleClient->respondsToKey =
            SCRIPT_ENVIRONMENT_CLIENT_RESPONDS_TO_KEY(
                return (key == "sample");
            );
        this->sampleClient->call =
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                MAIN_EXAMPLE_LOG("sample.call(%s)", key.c_str());
                return values;
            );
    }
    void tearSampleClientDown()
    {
        delete this->sampleClient;
    }
    void setupLuaEnvironment()
    {
        this->lua = new sol::state;
        this->lua->open_libraries();
        // Register Environment instance.
        (*this->lua)["ENV"] = this->environment;
        // Register Environment class.
        this->lua->new_usertype<script::Environment>(
            "Environment",
            // 'addClient' method.
            "addClient",
            &script::Environment::addClient,
            // 'call' method.
            "call",
            [](script::Environment &env, const std::string &key, sol::nested<script::EnvironmentClient::Values> values)
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
                            sol::nested<script::EnvironmentClient::Values> result = luaCallback(key, sol::as_table(values));
                            return std::move(result.source);
                        );
                }
            ),
            // 'respondsToKey' method.
            "respondsToKey",
            &script::EnvironmentClient::respondsToKey
        );
    }
    void tearLuaEnvironmentDown()
    {
        delete this->lua;
    }
    void loadCLIScript()
    {
        // Make sure `script` parameter exists.
        auto it = this->parameters.find("script");
        if (it == this->parameters.end())
        {
            return;
        }

        auto path = it->second;
        MAIN_EXAMPLE_LOG("TODO Load script at '%s'", path.c_str());

    }