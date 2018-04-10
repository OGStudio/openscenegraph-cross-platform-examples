FEATURE resources.h/Include
#include <osgDB/Registry>

FEATURE resources.h/Impl
osg::ref_ptr<osg::Node> node(Resource &resource, const std::string ext = "")
{
    osg::ref_ptr<osg::Node> node;
    // Get extension from resource's name if extension is not specified.
    std::string ex = ext.empty() ?  extension(resource) : ext;
    // Return empty node if extention is absent.
    if (ex.empty())
    {
        OSGCPE_RESOURCES_LOG(
            "ERROR Could not read node of '%s/%s' resource "
            "because extension is absent",
            resource.group.c_str(),
            resource.name.c_str()
        );
        return node.release();
    }
    auto reader = osgDB::Registry::instance()->getReaderWriterForExtension(ex);
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
            OSGCPE_RESOURCES_LOG(
                "ERROR Could not read node of '%s/%s' resource from buffer.",
                resource.group.c_str(),
                resource.name.c_str()
            );
        }
    }
    else
    {
        OSGCPE_RESOURCES_LOG(
            "ERROR Could not read node of '%s/%s' resource because "
            "node reader for extension '%s' is absent.",
            resource.group.c_str(),
            resource.name.c_str(),
            ex.c_str()
        );
    }
    return node.release();
}
