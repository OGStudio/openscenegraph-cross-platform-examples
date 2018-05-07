
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_HTTP_CLIENT_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_HTTP_CLIENT_H

// FEATURE HTTPClient-default/Include
// FEATURE HTTPClient-web/Include

namespace osgcpe
{

class HTTPClient
{
    public:
        typedef std::function<void(std::string)> Callback;

        HTTPClient(Callback success, Callback failure) :
            success(success),
            failure(failure),
            inProgress(false)
        {
            // FEATURE HTTPClient-default/Setup
            // FEATURE HTTPClient-web/Setup
        }
        ~HTTPClient()
        {
            // FEATURE HTTPClient-default/TearDown
            // FEATURE HTTPClient-web/TearDown
        }

        // FEATURE HTTPClient+get-default/Impl
        // FEATURE HTTPClient+get-web/Impl

        // Perform GET request.
        void get(const std::string &url)
        {
            auto connection = mg_connect_http(&this->client, handleEvent, url.c_str(), 0, 0);
            // Save 'this' point to the conection
            // for later referencing in callbacks.
            connection->user_data = this;
            this->inProgress = true;
        }

        bool needsProcessing()
        {
            return this->inProgress;
        }

        void process()
        {
            mg_mgr_poll(&this->client, 1000);
        }


#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_HTTP_CLIENT_H

