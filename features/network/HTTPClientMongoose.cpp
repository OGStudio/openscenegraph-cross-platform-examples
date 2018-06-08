FEATURE network.h/Impl
//! Internal class to implement HTTP GET/POST requests to HTTP(s) with Mongoose.
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
