FEATURE resource.h/Include
#include <osg/Texture2D>
#include <osgDB/Registry>

FEATURE resource.h/Impl
//! Set image for texture.

// \param texture Texture to set image for.
// \param resource Resource to take image from.
// \param ext (optional) If extension is present it won't be autodetected from the resource's name
void setTextureImage(
    osg::Texture2D *texture,
    const Resource &resource,
    const std::string ext = ""
) {
    // Get extension from resource's name if extension is not specified.
    std::string ex = ext.empty() ?  extension(resource) : ext;
    // Do nothing if extension is absent.
    if (ex.empty())
    {
        OSGCPE_RESOURCE_LOG(
            "ERROR Could not read image of '%s/%s' resource "
            "because extension is absent",
            resource.group.c_str(),
            resource.name.c_str()
        );
        return;
    }
    auto reader =
        osgDB::Registry::instance()->getReaderWriterForExtension(ex);
    if (reader)
    {
        ResourceStreamBuffer buf(resource);
        std::istream in(&buf);
        auto result = reader->readImage(in, 0);
        if (result.success())
        {
            // NOTE I could not get resulting osg::Image outside the function.
            // NOTE Somehow just returning result.getImage() does not work.
            texture->setImage(result.getImage());
        }
        else
        {
            OSGCPE_RESOURCE_LOG(
                "ERROR Could not read image of '%s/%s' resource from buffer.",
                resource.group.c_str(),
                resource.name.c_str()
            );
        }
    }
    else
    {
        OSGCPE_RESOURCE_LOG(
            "ERROR Could not read image of '%s/%s' resource because "
            "image reader for extension '%s' is absent.",
            resource.group.c_str(),
            resource.name.c_str(),
            ex.c_str()
        );
    }
}
