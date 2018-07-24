FEATURE network.h/Include
#include <string>
#include <vector>

FEATURE network.h/Impl
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
