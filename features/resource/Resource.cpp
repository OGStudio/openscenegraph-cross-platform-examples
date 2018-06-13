FEATURE resource.h/Impl
//! Resource container.
struct Resource
{
    Resource(
        const std::string &group,
        const std::string &name,
        unsigned char *contents,
        unsigned int len
    ) :
        group(group),
        name(name),
        contents(contents),
        len(len)
    { }

    std::string group;
    std::string name;
    unsigned char *contents;
    unsigned int len;
};
