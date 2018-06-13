FEATURE format.h/Impl
//! Split a string into a list of strings using a single character.
std::vector<std::string> splitString(const std::string &s, const char *c)
{
    size_t pos = 0;
    bool proceed = true;
    bool hasChar = false;
    std::vector<std::string> result;
    while (proceed)
    {
        auto id = s.find(c, pos);
        if (id != std::string::npos)
        {
            result.push_back(s.substr(pos, id - pos));
            pos = id + 1;
            hasChar = true;
        }
        else
        {
            result.push_back(s.substr(pos, s.length() - 1));
            proceed = false;
            // If delimiting char has not been found,
            // the result should only contain original string.
        }
    }
    return result;
}
