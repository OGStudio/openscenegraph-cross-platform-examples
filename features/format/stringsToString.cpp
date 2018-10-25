FEATURE format.h/Impl
//! Combine several strings into single one
std::string stringsToString(
    const std::vector<std::string> &strings,
    const std::string &separator = ", "
) {
    std::string result;
    for (auto item : strings)
    {
        // Items after the first one.
        if (!result.empty())
        {
            result += separator + item;
        }
        // First item.
        else
        {
            result = item;
        }
    }

    return result;
}
