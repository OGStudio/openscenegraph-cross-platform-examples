FEATURE main.h/Include
#include "script.lua.h"

FEATURE main.h/Setup
this->setupScriptingTest();

FEATURE main.h/TearDown
this->tearScriptingTestDown();

FEATURE main.h/Impl
private:
    void setupScriptingTest()
    {
        this->setupMouseTransmitter();
        this->setupCameraRepresentation();
        this->loadEmbeddedScript();
        this->loadCLIScript();
    }
    void tearScriptingTestDown()
    {
        this->tearCameraRepresentationDown();
        this->tearMouseTransmitterDown();
    }

    // Script loading.

    void loadEmbeddedScript()
    {
        MAIN_EXAMPLE_LOG("Loading embedded script");
        resource::Resource res(
            "scripts",
            "script.lua",
            script_lua,
            script_lua_len
        );
        auto contents = resource::string(res);
        // Execute the script.
        this->lua->script(contents);
        MAIN_EXAMPLE_LOG("Successfully loaded embedded script");
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
        MAIN_EXAMPLE_LOG("Loading script '%s'", path.c_str());
        std::ifstream localScript(path);
        if (localScript)
        {
            // Read file contents into string.
            std::string fileContents(
                (std::istreambuf_iterator<char>(localScript)),
                (std::istreambuf_iterator<char>())
            );
            // Execute the script.
            this->lua->script(fileContents);
            MAIN_EXAMPLE_LOG("Successfully loaded local script");
        }
        else
        {
            MAIN_EXAMPLE_LOG("ERROR Could not read local script");
        }
    }

    // Mouse transmitter.

    const std::string mouseCallbackName = "MouseTransmitter";

    void setupMouseTransmitter()
    {
        this->app->mouse->pressedButtonsChanged.addCallback(
            [=] {
                this->transmitMouseButtons();
            },
            this->mouseCallbackName
        );
    }
    void tearMouseTransmitterDown()
    {
        this->app->mouse->pressedButtonsChanged.removeCallback(
            this->mouseCallbackName
        );
    }
    void transmitMouseButtons()
    {
        // Convert buttons to string representation.
        auto buttons = this->app->mouse->pressedButtons;
        std::vector<std::string> strbuttons;
        for (auto button : buttons)
        {
            strbuttons.push_back(mouseButtonToString(button));
        }
        // Transmit.
        auto key = "application.mouse.pressedButtons";
        this->environment->call(key, strbuttons);
    }

    // Camera representation.

    script::EnvironmentClient *cameraClient;
    const std::string cameraKeyPrefix = "application.camera.";

    void setupCameraRepresentation()
    {
        this->cameraClient = new script::EnvironmentClient;
        this->environment->addClient(this->cameraClient);
        this->cameraClient->respondsToKey =
            SCRIPT_ENVIRONMENT_CLIENT_RESPONDS_TO_KEY(
                return format::stringStartsWith(key, this->cameraKeyPrefix);
            );
        this->cameraClient->call =
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                return this->processCamera(key, values);
            );
    }
    void tearCameraRepresentationDown()
    {
        delete this->cameraClient;
    }
    script::EnvironmentClient::Values processCamera(
        const std::string &key,
        const script::EnvironmentClient::Values &values
    ) {
        auto cameraKey = key.substr(this->cameraKeyPrefix.length());
        script::EnvironmentClient::Values empty;
        if (cameraKey == "clearColor")
        {
            // Set.
            if (!values.empty())
            {
                // Make sure there are three components.
                if (values.size() != 3)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set key '%s' "
                        "because values' count is not 3"
                    );
                    return empty;
                }

                // Apply color.
                auto color = this->app->camera()->getClearColor();
                color.r() = atof(values[0].c_str());
                color.g() = atof(values[1].c_str());
                color.b() = atof(values[2].c_str());
                this->app->camera()->setClearColor(color);
            }

            // Return current color for Get and after successful Set.
            auto color = this->app->camera()->getClearColor();
            return {
                format::printfString("%f", color.r()),
                format::printfString("%f", color.g()),
                format::printfString("%f", color.b()),
            };
        }

        MAIN_EXAMPLE_LOG(
            "ERROR No camera handler for key '%s'",
            key.c_str()
        );
        return empty;
    }
