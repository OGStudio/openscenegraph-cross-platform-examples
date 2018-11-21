FEATURE main.h/Include
#include <fstream>

FEATURE main.h/Setup
this->loadCLIScript();

FEATURE main.h/Impl
private:
    void loadCLIScript()
    {
        // Make sure `script` parameter exists.
        auto it = this->parameters.find("script");
        if (it == this->parameters.end())
        {
            return;
        }

        auto path = it->second;
        MAIN_EXAMPLE_LOG("Loading a script from '%s'", path.c_str());
        std::ifstream localScript(path);
        if (localScript)
        {
            // Read file contents into string.
            std::string fileContents(
                (std::istreambuf_iterator<char>(localScript)),
                (std::istreambuf_iterator<char>())
            );
            this->executeScript(fileContents);
        }
        else
        {
            MAIN_EXAMPLE_LOG("ERROR Could not read the script");
        }
    }
