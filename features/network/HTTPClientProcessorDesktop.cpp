FEATURE network.h/Impl
//! Perform HTTP GET/POST requests using Mongoose.
class HTTPClientProcessorDesktop
{
    public:
        HTTPClientProcessorDekstop(HTTPClient *client) : client(client) { }

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
                auto processor = new HTTPRequestProcessorMongoose(request);
                this->processors.append(processor);
            }
        }

    private:
        HTTPClient *client;
        std::vector<HTTPRequestProcessorMongoose *> processors;
};
