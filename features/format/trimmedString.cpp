FEATURE format.h/Impl
//! Trim non-visible characters at the beginning and at the end.
std::string trimmedString(const std::string &s)
{
    // Source: https://stackoverflow.com/a/21698913
    // Topic: What's the best way to trim std::string?

    // Find the first position without space characters.
    std::string::const_iterator it = s.begin();
    while (
        (it != s.end()) &&
        std::isspace(*it)
    ) {
        ++it;
    }

    // Find the last position without space characters.
    std::string::const_reverse_iterator rit = s.rbegin();
    while (
        (rit.base() != it) &&
        std::isspace(*rit)
    ) {
        ++rit;
    }

    return std::string(it, rit.base());
}
