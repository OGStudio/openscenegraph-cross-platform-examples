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

    std::string query = argv[2];
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

    // Add "index" parameter that is everything
    // before "?" and the search string.
    std::string url(argv[1]);
    // Assume no parameters by default.
    parameters["index"] = url;
    // Rewrite if there were parameters after all.
    if (query.length())
    {
        auto pos = url.find("?");
        parameters["index"] = url.substr(0, pos);
    }

    return parameters;
}
