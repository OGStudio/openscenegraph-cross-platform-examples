FEATURE resource.h/Impl
//! Resource container.
struct Resource
{
    Resource(
        const std::string &group,
        const std::string &name,
        const std::string &contents
    ) :
        group(group),
        name(name),
        contents(contents)
    { }

    Resource(
        const std::string &group,
        const std::string &name,
        const unsigned char *contents,
        unsigned int len
    ) :
        group(group),
        name(name)
    {
        this->contents =
            std::string(
                reinterpret_cast<const char *>(contents),
                len
            );
    }

    std::string group;
    std::string name;
    std::string contents;
};
