
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
            this->request(url, 0);
        }

        // Perform POST request.
        void post(const std::string &url, const std::string &data)
        {
            this->request(url, data.c_str());
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

        void request(const std::string &url, const char *data)
        {
            // Ignore new requests if already in progress.
            if (this->inProgress)
            {
                return;
            }

            this->inProgress = true;

            // Set request method.
            std::string method = "GET";
            if (data)
            {
                method = "POST";
                // Set headers.
                const char *headers[] = {
                    "Content-Type", "text/plain",
                    0
                };
                this->client.requestHeaders = headers;
                // Set body.
                this->client.requestData = data;
                this->client.requestDataSize = strlen(data);
            }
            strcpy(this->client.requestMethod, method.c_str());

            // Set callbacks.
            this->client.onsuccess = handleSuccess;
            this->client.onerror = handleFailure;

            // Perform the request.
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

// HTTPClientFetch+Stub Start
// Stub.
// HTTPClientFetch+Stub End

