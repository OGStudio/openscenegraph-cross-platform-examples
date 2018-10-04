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

    }
    void tearLuaEnvironmentDown()
    {
        delete this->lua;
    }
