FEATURE network.h/Include
#include <functional>
#include <string>
#include <vector>

FEATURE network.h/Begin
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

FEATURE network.h/End
    private:
        std::vector<HTTPClientImpl *> clients;

        HTTPClientImpl *createHTTPClient(
            Callback success,
            Callback failure
        ) {
            return new HTTPClientImpl(success, failure);
        }
};
