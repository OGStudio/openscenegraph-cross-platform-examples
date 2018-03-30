
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_INFO_VISITOR_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_INFO_VISITOR_H

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/NodeVisitor>

namespace osgcpe
{

// This class forces the use of VBO.
class InfoVisitor : public osg::NodeVisitor
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
            auto msg =
                printfString(
                    "%s%s::%s",
                    this->spaces().c_str(),
                    node.libraryName(),
                    node.className()
                );
            platformLog(msg.c_str());
            ++this->level;
            this->traverse(node);
            --this->level;
        }
        virtual void apply(osg::Geode &geode)
        {
            auto msg =
                printfString(
                    "%s%s::%s",
                    this->spaces().c_str(),
                    geode.libraryName(),
                    geode.className()
                );
            platformLog(msg.c_str());
            ++this->level;
            for (auto i = 0; i < geode.getNumDrawables(); ++i)
            {
                auto drawable = geode.getDrawable(i);
                auto msg =
                    printfString(
                        "%s%s::%s",
                        this->spaces().c_str(),
                        drawable->libraryName(),
                        drawable->className()
                    );
                platformLog(msg.c_str());
            }
            this->traverse(geode);
            --this->level;
        }

    private:
        unsigned int level;
};

} // namespace osgcpe

// FEATURE InfoVisitor+Stub/Impl

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_INFO_VISITOR_H

