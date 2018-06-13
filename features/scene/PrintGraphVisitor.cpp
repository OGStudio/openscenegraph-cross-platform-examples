FEATURE scene.h/Include
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/NodeVisitor>

FEATURE scene.h/Impl
//! Print scene graph structure.
class PrintGraphVisitor : public osg::NodeVisitor
{
    public:
        InfoVisitor() :
            osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
            level(0)
        { }

        std::string spaces()
        {
            return std::string(this->level * 2, ' ');
        }

        virtual void apply(osg::Node &node)
        {
            log::logprintf(
                "%s%s::%s",
                this->spaces().c_str(),
                node.libraryName(),
                node.className()
            );
            ++this->level;
            this->traverse(node);
            --this->level;
        }
        virtual void apply(osg::Geode &geode)
        {
            log::logprintf(
                "%s%s::%s",
                this->spaces().c_str(),
                geode.libraryName(),
                geode.className()
            );
            ++this->level;
            for (auto i = 0; i < geode.getNumDrawables(); ++i)
            {
                auto drawable = geode.getDrawable(i);
                log::logprintf(
                    "%s%s::%s",
                    this->spaces().c_str(),
                    drawable->libraryName(),
                    drawable->className()
                );
            }
            this->traverse(geode);
            --this->level;
        }

    private:
        unsigned int level;
};
