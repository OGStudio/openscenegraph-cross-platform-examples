FEATURE format.h/Include
#include <map>

FEATURE format.h/Impl
typedef std::map<std::string, std::string> Parameters;
//! Convert command line arguments in the form of `--key=value` to parameters.
Parameters commandLineArgumentsToParameters(
    int argc,
    char *argv[]
) {
    Parameters parameters;
    // Start with index #1 because index #0 contains program name.
    for (auto i = 1; i < argc; ++i)
    {
        auto argument = std::string(argv[i]);
        // Only accept arguments starting with `--`.
        if (format::stringStartsWith(argument, "--"))
        {
            // Skip the dashes.
            auto option = argument.substr(2);
            auto keyAndValue = format::splitString(option, "=");
            if (keyAndValue.size() == 2)
            {
                auto key = keyAndValue[0];
                auto value = keyAndValue[1];
                parameters[key] = value;
            }
        }
    }
    return parameters;
}
