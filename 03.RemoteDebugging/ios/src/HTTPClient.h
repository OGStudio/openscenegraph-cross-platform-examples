
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
            auto client = new HTTPClientMongoose(success, failure);
            client->get(url);
            this->clients.push_back(client);
        }

        void post(
            const std::string &url,
            const std::string &data,
            Callback success,
            Callback failure
        ) {
            auto client = new HTTPClientMongoose(success, failure);
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
                this->clients.erase(this->clients.begin() + clientId);
            }
        }

    private:
        std::vector<HTTPClientMongoose *> clients;
};

// HTTPClient+Stub Start
// Stub.
// HTTPClient+Stub End

