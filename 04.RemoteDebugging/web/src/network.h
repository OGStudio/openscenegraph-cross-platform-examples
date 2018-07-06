
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

#include "network-extlib.h"

// OSGCPE_NETWORK_HTTP_CLIENT_FETCH_LOG Start
#include "log.h"
#include "format.h"
#define OSGCPE_NETWORK_HTTP_CLIENT_FETCH_LOG_PREFIX "osgcpe::network::HTTPClientFetch(%p) %s"
#define OSGCPE_NETWORK_HTTP_CLIENT_FETCH_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_NETWORK_HTTP_CLIENT_FETCH_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )
// OSGCPE_NETWORK_HTTP_CLIENT_FETCH_LOG End

namespace osgcpe
{
namespace network
{

// HTTPClientFetch Start
//! Internal class to implement HTTP GET/POST requests to HTTP(s) with Emscripten's FetchAPI.
class HTTPClientFetch
{
    public:
        typedef std::function<void(std::string)> Callback;

        HTTPClientFetch(Callback success, Callback failure) :
            success(success),
            failure(failure),
            inProgress(false)
        {
            emscripten_fetch_attr_init(&this->client);
            this->client.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
            // Save 'this' pointer to reference it in callbacks.
            this->client.userData = this;
        }

        ~HTTPClientFetch()
        {
            this->client.userData = 0;
        }

        // Perform GET request.
        void get(const std::string &url)
        {
            this->request(url, "");
        }

        // Perform POST request.
        void post(const std::string &url, const std::string &data)
        {
            this->request(url, data);
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
        Callback success;
        Callback failure;
        bool inProgress;
        std::string data;

        void request(const std::string &url, const std::string &data)
        {
            // Ignore new requests if already in progress.
            if (this->inProgress)
            {
                return;
            }

            this->inProgress = true;
            // Keep sent data because FetchAPI needs it outside this scope.
            this->data = data;

            // Set request method.
            std::string method = "GET";
            if (this->data.length())
            {
                method = "POST";
            }
            strcpy(this->client.requestMethod, method.c_str());
            // Set body.
            if (this->data.length())
            {
                /*
                // Set headers.
                const char *headers[] = {
                    "Content-Type", "text/plain; charset=utf-8",
                    0
                };
                this->client.requestHeaders = headers;
                */
                // Set body.
                this->client.requestData = this->data.c_str();
                this->client.requestDataSize = strlen(this->data.c_str());
                /*
                OSGCPE_NETWORK_HTTP_CLIENT_FETCH_LOG(
                    "request data: '%s' len: '%d'",
                    this->client.requestData,
                    this->client.requestDataSize
                );
                */
            }

            // Set callbacks.
            this->client.onsuccess = handleSuccess;
            this->client.onerror = handleFailure;

            // Perform request.
            emscripten_fetch(&this->client, url.c_str());
        }

        static void handleSuccess(emscripten_fetch_t *fetch)
        {
            auto self = reinterpret_cast<HTTPClientFetch *>(fetch->userData);
            if (self)
            {
                self->inProgress = false;
                // TODO Come up with a way to receive response not limited in size.
                const int BUF_SIZE = 1024;
                // Get the body.
                if (fetch->numBytes < BUF_SIZE)
                {
                    char buf[BUF_SIZE];
                    strncpy(buf, fetch->data, fetch->numBytes);
                    buf[fetch->numBytes + 1] = '\0';
                    std::string body(buf);
                    // Report success.
                    self->success(body);
                }
                else
                {
                    // Report failure.
                    self->failure("Failed due to incoming data overflow");
                }
            }
            // Free data associated with this request.
            emscripten_fetch_close(fetch);
        }

        static void handleFailure(emscripten_fetch_t *fetch)
        {
            auto self = reinterpret_cast<HTTPClientFetch *>(fetch->userData);
            if (self)
            {
                self->inProgress = false;
                // TODO Report status code? fetch->status
                self->failure("Failed");
            }
            // Free data associated with this request.
            emscripten_fetch_close(fetch);
        }
};
// HTTPClientFetch End


// HTTPClient Start
//! Perform HTTP GET/POST request to HTTP(s).

//! Notes:
//! - Uses HTTPClientFetch internal class under web.
//! - Uses HTTPClientMongoose internal class under desktop and mobile.
class HTTPClient
{
    public:
        typedef std::function<void(std::string)> Callback;

        HTTPClient()
        {
        }
        ~HTTPClient()
        {
            for (auto client : this->clients)
            {
                delete client;
            }
        }

        void get(const std::string &url, Callback success, Callback failure)
        {
            auto client = this->createHTTPClient(success, failure);
            client->get(url);
            this->clients.push_back(client);
        }

        void post(
            const std::string &url,
            const std::string &data,
            Callback success,
            Callback failure
        ) {
            auto client = this->createHTTPClient(success, failure);
            client->post(url, data);
            this->clients.push_back(client);
        }

        bool needsProcessing()
        {
            for (auto client : this->clients)
            {
                if (client->needsProcessing())
                {
                    return true;
                }
            }
            return false;
        }

        void process()
        {
            std::vector<ssize_t> clientIdsToRemove;

            ssize_t id = 0;
            for (auto client : this->clients)
            {
                // Process.
                if (client->needsProcessing())
                {
                    client->process();
                }
                // Schedule client for removal if it no longer needs processing.
                else
                {
                    clientIdsToRemove.push_back(id);
                }
                ++id;
            }

            // Remove scheduled clients. Loop in reverse order.
            auto it = clientIdsToRemove.rbegin();
            for (; it != clientIdsToRemove.rend(); ++it)
            {
                auto clientId = *it;
                auto client = this->clients[clientId];
                // Erase client entry.
                this->clients.erase(this->clients.begin() + clientId);
                // Deallocate the client.
                delete client;
            }
        }

// HTTPClient End
    // HTTPClient+Fetch Start
    private:
        typedef HTTPClientFetch HTTPClientImpl;
    // HTTPClient+Fetch End
// HTTPClient Start
    private:
        std::vector<HTTPClientImpl *> clients;

        HTTPClientImpl *createHTTPClient(
            Callback success,
            Callback failure
        ) {
            return new HTTPClientImpl(success, failure);
        }
};
// HTTPClient End

} // namespace network
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_NETWORK_H

