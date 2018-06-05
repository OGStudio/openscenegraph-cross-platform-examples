
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

class HTTPClientMongoose
{
    public:
        typedef std::function<void(std::string)> Callback;

        HTTPClientMongoose(Callback success, Callback failure) :
            success(success),
            failure(failure),
            inProgress(false)
        {
            mg_mgr_init(&this->client, 0);
        }

        ~HTTPClientMongoose()
        {
            mg_mgr_free(&this->client);
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
            const int delay = 100;
            mg_mgr_poll(&this->client, delay);
        }

    private:
        mg_mgr client;
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

            // Perform request.
            auto connection = mg_connect_http(&this->client, handleEvent, url.c_str(), 0, data);
            // Save 'this' pointer to reference it in callbacks.
            connection->user_data = this;
        }

        static void handleEvent(mg_connection *connection, int event, void *data)
        {
            auto self =
                reinterpret_cast<HTTPClientMongoose *>(connection->user_data);
            switch (event)
            {
                case MG_EV_CONNECT:
                    {
                        auto status = *static_cast<int *>(data);
                        if (status != 0)
                        {
                            //self->failure(strerror(status));
                            self->failure("Failed to connect");
                            self->inProgress = false;
                        }
                    }
                    break;
                case MG_EV_HTTP_REPLY:
                    {
                        connection->flags |= MG_F_CLOSE_IMMEDIATELY;
                        auto msg = static_cast<http_message *>(data);
                        auto body = std::string(msg->body.p, msg->body.len);
                        self->inProgress = false;
                        self->success(body);
                    }
                    break;
                case MG_EV_CLOSE:
                    // Only report failure if CLOSE event precedes REPLY one.
                    if (self->inProgress)
                    {
                        self->failure("Server closed connection");
                    }
                    self->inProgress = false;
                    break;
                default:
                    break;
            }
        }

};

// FEATURE HTTPClientMongoose+Stub/Impl

