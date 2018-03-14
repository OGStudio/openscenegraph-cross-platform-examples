FEATURE resources.h/Include
#include <osgDB/Registry>

FEATURE resources.h/Impl
osg::Node *resourceNode(Resource &resource, const std::string extension)
{
    auto reader =
        osgDB::Registry::instance()->getReaderWriterForExtension(extension);
    if (reader)
    {
        ResourceStreamBuffer buf(resource);
        std::istream in(&buf);
        auto result = reader->readNode(in, 0);
        if (result.success())
        {
            return result.getNode();
        }
        else
        {
            auto errmsg =
                printfString(
                    "ERROR Could not read node of '%s' resource from buffer.",
                    resource.name.c_str()
                );
            platformLog(errmsg.c_str());
        }
    }
    else
    {
        auto errmsg =
            printfString(
                "ERROR Could not read node of '%s' resource because "
                "node reader for extension '%s' is absent.",
                resource.name.c_str(),
                extension.c_str()
            );
        platformLog(errmsg.c_str());
    }
}
