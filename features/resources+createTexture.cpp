FEATURE resources.h/Include
#include <osg/Texture2D>

FEATURE resources.h/Impl
//! Create texture from a resource.
osg::Texture2D *createTexture(const Resource &resource)
{
    osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
    setTextureImage(tex, resource);
    tex->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT);
    tex->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::REPEAT);
    tex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
    tex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    return tex.release();
}
