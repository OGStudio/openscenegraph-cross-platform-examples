FEATURE resource.h/Include
#include <osg/Texture2D>
#include <osgDB/Registry>

FEATURE resource.h/Impl
//! Set image for texture from std::istream.

// \param texture Texture to set image for.
// \param in Input stream to take image from.
// \param ext Extension to find suitable plugin.
void setTextureImage(
    osg::Texture2D *texture,
    std::istream &in,
    const std::string ext
) {
    auto reader =
        osgDB::Registry::instance()->getReaderWriterForExtension(ext);
    if (reader)
    {
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
                "ERROR Could not read image of 'TODO' resource from buffer."//,
                //resource.group.c_str(),
                //resource.name.c_str()
            );
        }
    }
    else
    {
        OSGCPE_RESOURCE_LOG(
            "ERROR Could not read image of 'TODO' resource because "
            "image reader for extension '%s' is absent.",
            //resource.group.c_str(),
            //resource.name.c_str(),
            ext.c_str()
        );
    }
}
