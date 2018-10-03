FEATURE main.h/Include
#include "script.h"

FEATURE main.h/Setup
this->setupScriptingTest();

FEATURE main.h/TearDown
this->tearScriptingTestDown();

FEATURE main.h/Impl
private:
    script::Environment *environment;
    script::EnvironmentClient *sampleClient;
    void setupScriptingTest()
    {
        this->environment = new script::Environment;

        // Setup sample environment client in C++.
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

        // Call sample client through Environment interface.
        auto values = this->environment->call("sample", {"A", "B", "C"});
        for (auto value : values)
        {
            MAIN_EXAMPLE_LOG("sample. value: '%s'", value.c_str());
        }
    }
    void tearScriptingTestDown()
    {
        delete this->environment;
        delete this->sampleClient;
    }
