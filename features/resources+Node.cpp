FEATURE resources.h/Include
#include <osgDB/Registry>

FEATURE resources.h/Impl
osg::ref_ptr<osg::Node> resourceNode(Resource &resource, const std::string extension)
{
    osg::ref_ptr<osg::Node> node;
    auto reader =
        osgDB::Registry::instance()->getReaderWriterForExtension(extension);
    if (reader)
    {
        ResourceStreamBuffer buf(resource);
        std::istream in(&buf);
        auto result = reader->readNode(in, 0);
        if (result.success())
        {
            node = result.getNode();
        }
        else
        {
            log::logprintf(
                "ERROR Could not read node of '%s' resource from buffer.",
                resource.name.c_str()
            );
        }
    }
    else
    {
        log::logprintf(
            "ERROR Could not read node of '%s' resource because "
            "node reader for extension '%s' is absent.",
            resource.name.c_str(),
            extension.c_str()
        );
    }
    return node.release();
}
