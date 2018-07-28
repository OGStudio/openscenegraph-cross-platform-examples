
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
// HTTPRequest Start
#include <functional>
#include <string>

// HTTPRequest End
// HTTPRequestProcessorMongoose Start
#include "format.h"

// HTTPRequestProcessorMongoose End

namespace osgcpe
{
namespace network
{

// HTTPRequest Start
//! HTTP request container
class HTTPRequest
{
    public:
        typedef std::function<void(std::string)> Callback;

        enum STATUS
        {
            PENDING,
            IN_PROGRESS,
            COMPLETED
        };

        // If data is emtpy, GET request is issued.
        // Otherwise POST request is issued.
        HTTPRequest(
            const std::string &url,
            const std::string &data,
            Callback success,
            Callback failure
        ) :
            url(url),
            data(data),
            success(success),
            failure(failure),
            status(PENDING)
        { }

        const std::string url;
        const std::string data;
        Callback success;
        Callback failure;
        STATUS status;
};
// HTTPRequest End
// HTTPRequestProcessorMongoose Start
//! Internal class to process HTTP GET/POST requests with Mongoose.
class HTTPRequestProcessorMongoose
{
    public:
        HTTPRequestProcessorMongoose(HTTPRequest *request) :
            request(request),
            inProgress(false)
        {
            mg_mgr_init(&this->client, 0);
            this->processRequest();
        }

        ~HTTPRequestProcessorMongoose()
        {
            mg_mgr_free(&this->client);
        }

        bool needsProcessing() const
        {
            return this->inProgress;
        }

        void process()
        {
            const int delay = 100;
            mg_mgr_poll(&this->client, delay);
        }

    private:
        mg_mgr client;
        HTTPRequest *request;
        bool inProgress;

        void processRequest()
        {
            this->inProgress = true;
            this->request->status = HTTPRequest::IN_PROGRESS;

            auto url = this->request->url.c_str();
            const char *data =
                this->request->data.length() ?
                this->request->data.c_str() :
                0;
            // Perform request.
            auto connection =
                mg_connect_http(&this->client, this->handleEvent, url, 0, data);
            // Save 'this' pointer to reference it in callbacks.
            connection->user_data = this;
        }

        static void handleEvent(
            mg_connection *connection,
            int event,
            void *data
        ) {
            auto self =
                reinterpret_cast<HTTPRequestProcessorMongoose *>(
                    connection->user_data
                );
            auto request = self->request;
            switch (event)
            {
                case MG_EV_CONNECT:
                    {
                        auto status = *static_cast<int *>(data);
                        if (status != 0)
                        {
                            request->status = HTTPRequest::COMPLETED;
                            auto msg = format::printfString("Failed to connect: '%s'", strerror(status));
                            request->failure(msg);
                            self->inProgress = false;
                        }
                    }
                    break;
                case MG_EV_HTTP_REPLY:
                    {
                        connection->flags |= MG_F_CLOSE_IMMEDIATELY;
                        auto msg = static_cast<http_message *>(data);
                        auto body = std::string(msg->body.p, msg->body.len);
                        request->status = HTTPRequest::COMPLETED;
                        request->success(body);
                        self->inProgress = false;
                    }
                    break;
                case MG_EV_CLOSE:
                    // Only report failure if CLOSE event precedes REPLY one.
                    if (self->inProgress)
                    {
                        request->status = HTTPRequest::COMPLETED;
                        request->failure("Server closed connection");
                    }
                    self->inProgress = false;
                    break;
                default:
                    break;
            }
        }
};
// HTTPRequestProcessorMongoose End
// HTTPRequestProcessorMongoose Start
typedef HTTPRequestProcessorMongoose HTTPRequestProcessor;

// HTTPRequestProcessorMongoose End

// HTTPClient Start
//! Use HTTPClient to perform HTTP(s) GET/POST requests.

//! Platform specific entities regularly poll HTTPClient for pending requests
//! and perform them. Once a request is done, platform specific entities
//! report result back to HTTPClient.
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
// HTTPClientProcessor Start
//! Perform HTTP GET/POST requests using either Mongoose, or FetchAPI.
class HTTPClientProcessor
{
    public:
        HTTPClientProcessor(HTTPClient *client) : client(client) { }

        void process()
        {
            // Process active requests and schedule completed ones for removal.
            ssize_t id = 0;
            std::vector<ssize_t> idsToRemove;
            for (auto processor : this->processors)
            {
                // Process.
                if (processor->needsProcessing())
                {
                    processor->process();
                }
                // Schedule completed processor for removal.
                else
                {
                    idsToRemove.push_back(id);
                }
                ++id;
            }

            // Remove scheduled processors. Loop in reverse order.
            auto it = idsToRemove.rbegin();
            for (; it != idsToRemove.rend(); ++it)
            {
                auto id = *it;
                auto processor = this->processors[id];
                // Erase entry.
                this->processors.erase(this->processors.begin() + id);
                // Remove processor.
                delete processor;
            }

            // Created new processors for pending requests.
            auto pendingRequests = this->client->pendingRequests();
            for (auto request : pendingRequests)
            {
                auto processor = new HTTPRequestProcessor(request);
                this->processors.push_back(processor);
            }
        }

    private:
        HTTPClient *client;
        std::vector<HTTPRequestProcessor *> processors;
};
// HTTPClientProcessor End

} // namespace network
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_NETWORK_H

