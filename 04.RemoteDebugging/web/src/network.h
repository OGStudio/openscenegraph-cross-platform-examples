
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

// fetch Start
#include <emscripten/fetch.h>
// fetch End
// HTTPClient Start
#include <string>
#include <vector>

// HTTPClient End
// HTTPRequest Start
#include <functional>
#include <string>

// HTTPRequest End
// HTTPRequestProcessorFetch Start
#include "format.h"

// HTTPRequestProcessorFetch End

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
// HTTPRequestProcessorFetch Start
//! Internal class to process HTTP GET/POST requests with FetchAPI.
class HTTPRequestProcessorFetch
{
    public:
        HTTPRequestProcessorFetch(HTTPRequest *request) :
            request(request),
            inProgress(false)
        {
            emscripten_fetch_attr_init(&this->client);
            this->client.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
            // Save 'this' pointer to reference it in callbacks.
            this->client.userData = this;
            // Start.
            this->processRequest();
        }

        ~HTTPRequestProcessorFetch()
        {
            this->client.userData = 0;
        }

        bool needsProcessing() const
        {
            return this->inProgress;
        }

        void process()
        {
            // Do nothing.
            // Emscripten's Fetch API does actual polling.
        }

    private:
        emscripten_fetch_attr_t client;
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

            // Set request method.
            std::string method = "GET";
            if (data)
            {
                method = "POST";
            }
            strcpy(this->client.requestMethod, method.c_str());

            // Set body.
            if (data)
            {
                /*
                // Set headers.
                const char *headers[] = {
                    "Content-Type", "text/plain; charset=utf-8",
                    0
                };
                this->client.requestHeaders = headers;
                */
                this->client.requestData = data;
                this->client.requestDataSize = strlen(data);
            }

            // Set callbacks.
            this->client.onsuccess = handleSuccess;
            this->client.onerror = handleFailure;

            // Perform request.
            emscripten_fetch(&this->client, url);
        }

        static void handleSuccess(emscripten_fetch_t *fetch)
        {
            auto self =
                reinterpret_cast<HTTPRequestProcessorFetch *>(fetch->userData);
            if (self)
            {
                self->inProgress = false;
                std::string body(fetch->data, fetch->numBytes);
                // Report success.
                auto request = self->request;
                request->status = HTTPRequest::COMPLETED;
                request->success(body);
            }
            // Free data associated with this request.
            emscripten_fetch_close(fetch);
        }

        static void handleFailure(emscripten_fetch_t *fetch)
        {
            auto self =
                reinterpret_cast<HTTPRequestProcessorFetch *>(fetch->userData);
            if (self)
            {
                self->inProgress = false;
                auto msg = format::printfString("Failed. Status code: '%d'", fetch->status);
                // Report failure.
                auto request = self->request;
                request->status = HTTPRequest::COMPLETED;
                request->failure(msg);
            }
            // Free data associated with this request.
            emscripten_fetch_close(fetch);
        }
};
// HTTPRequestProcessorFetch End
// HTTPRequestProcessorFetch Start
typedef HTTPRequestProcessorFetch HTTPRequestProcessor;

// HTTPRequestProcessorFetch End

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

