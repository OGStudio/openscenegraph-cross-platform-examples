FEATURE resource.h/Impl
bool isPathRemote(const std::string &path)
{
    return
        format::stringStartsWith(path, "http://") ||
        format::stringStartsWith(path, "https://")
        ;
}

