
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RESOURCE_STREAM_BUFFER_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RESOURCE_STREAM_BUFFER_H

#include "Resource.h"

namespace osgcpe
{

//! Work with Resource contents as with any stream.
struct ResourceStreamBuffer : std::streambuf
{
    ResourceStreamBuffer(const Resource &resource)
    {
        char *contents = reinterpret_cast<char *>(resource.contents);
        this->setg(contents, contents, contents + resource.len);
    }
    // Implement 'seekoff()' to support 'seekg()' calls.
    // OpenSceneGraph plugins like OSG and ImageIO use 'seekg()'.
    // Topic: How to implement custom std::streambuf's seekoff()?
    // Source: https://stackoverflow.com/a/46068920
    std::streampos seekoff(
        std::streamoff off,
        std::ios_base::seekdir dir,
        std::ios_base::openmode which = std::ios_base::in
    ) {
        if (dir == std::ios_base::cur)
            this->gbump(off);
        else if (dir == std::ios_base::end)
            this->setg(this->eback(), this->egptr() + off, this->egptr());
        else if (dir == std::ios_base::beg)
            this->setg(this->eback(), this->eback() + off, this->egptr());
        return this->gptr() - this->eback();
    }
};


} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_RESOURCE_STREAM_BUFFER_H

