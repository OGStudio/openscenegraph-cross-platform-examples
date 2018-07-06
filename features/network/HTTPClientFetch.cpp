FEATURE network.h/Impl
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
                auto msg = format::printfString("Failed. Status code: '%d'", fetch->status);
                self->failure(msg);
            }
            // Free data associated with this request.
            emscripten_fetch_close(fetch);
        }
};
