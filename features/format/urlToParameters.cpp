FEATURE format.h/Include
#include <map>

FEATURE format.h/Impl
typedef std::map<std::string, std::string> Parameters;
//! Convert query parameters starting after `?` that are in the form of `key=value` to parameters.
Parameters urlToParameters(int argc, char *argv[])
{
    Parameters parameters;

    // No URL has been provided. Nothing to parse.
    if (argc < 3)
    {
        return parameters;
    }

    auto query = argv[2];
    auto options = format::splitString(query, "&");

    for (auto option : options)
    {
        auto keyAndValue = format::splitString(option, "=");
        if (keyAndValue.size() == 2)
        {
            auto key = keyAndValue[0];
            auto value = keyAndValue[1];
            parameters[key] = value;
        }
    }

    // Add "base" parameter.
    parameters["base"] = argv[1];

    return parameters;
}
