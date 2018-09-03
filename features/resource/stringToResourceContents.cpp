FEATURE resource.h/Impl
unsigned char * stringToResourceContents(const std::string &str)
{
    auto dat = const_cast<char *>(str.data());
    if (!dat)
    {
        RESOURCE_LOG(
            "ERROR Could not convert string to resource contents "
            "at 'const char * -> char *' stage"
        );
        return 0;
    }
    auto contents = reinterpret_cast<unsigned char *>(dat);
    if (!contents)
    {
        RESOURCE_LOG(
            "ERROR Could not convert string to resource contents "
            "at 'char * -> usigned char *' stage"
        );
        return 0;
    }

    return contents;
}
