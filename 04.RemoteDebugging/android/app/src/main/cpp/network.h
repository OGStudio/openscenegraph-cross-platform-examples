
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_NETWORK_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_NETWORK_H

// extlib-mongoose Start
#include "network-extlib.h"

// extlib-mongoose End
// HTTPClient Start
#include <string>
#include <vector>

// HTTPClient End

namespace osgcpe
{
namespace network
{


// HTTPClient Start
//! Perform HTTP(s) GET/POST requests by place HTTP requests processed by other entity.
class HTTPClient
{
    public:
        HTTPClient()
        { }
        ~HTTPClient()
        { }

        typedef std::vector<HTTPRequest *> Requests;

        void get(
            const std::string &url,
            HTTPRequest::Callback success,
            HTTPRequest::Callback failure
        ) {
            auto request = new HTTPRequest(url, "", success, failure);
            this->requests.push_back(request);
        }

        void post(
            const std::string &url,
            const std::string &data,
            HTTPRequest::Callback success,
            HTTPRequest::Callback failure
        ) {
            auto request = new HTTPRequest(url, data, success, failure);
            this->requests.push_back(request);
        }

        HTTPRequest *nextPendingRequest()
        {
            this->removeCompletedRequests();

            for (auto request : this->requests)
            {
                if (request->status == HTTPRequest::PENDING)
                {
                    return request;
                }
            }
            return 0;
        }

        Requests pendingRequests()
        {
            this->removeCompletedRequests();

            Requests pending;
            for (auto request : this->requests)
            {
                if (request->status == HTTPRequest::PENDING)
                {
                    pending.push_back(request);
                }
            }
            return pending;
        }

    private:
        Requests requests;

        void removeCompletedRequests()
        {
            // Collect ids of requests to remove.
            std::vector<ssize_t> idsToRemove;
            {
                ssize_t id = 0;
                for (auto request : this->requests)
                {
                    if (request->status == HTTPRequest::COMPLETED)
                    {
                        idsToRemove.push_back(id);
                    }
                    ++id;
                }
            }

            // Remove completed requests. Loop in reverse order.
            auto it = idsToRemove.rbegin();
            for (; it != idsToRemove.rend(); ++it)
            {
                auto id = *it;
                auto request = this->requests[id];
                // Erase request entry.
                this->requests.erase(this->requests.begin() + id);
                // Delete request.
                delete request;
            }
        }
};
// HTTPClient End

} // namespace network
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_NETWORK_H

