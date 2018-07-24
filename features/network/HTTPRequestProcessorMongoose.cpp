FEATURE network.h/Include
#include "format.h"

FEATURE network.h/TypeDef
typedef HTTPRequestProcessorMongoose HTTPRequestProcessor;

FEATURE network.h/Impl
//! Internal class to process HTTP GET/POST requests with Mongoose.
class HTTPRequestProcessorMongoose
{
    public:
        HTTPRequestProcessorMongoose(HTTPRequest *request) :
            request(request),
            inProgress(false)
        {
            mg_mgr_init(&this->client, 0);
            this->processRequest();
        }

        ~HTTPRequestProcessorMongoose()
        {
            mg_mgr_free(&this->client);
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
            // Perform request.
            auto connection =
                mg_connect_http(&this->client, this->handleEvent, url, 0, data);
            // Save 'this' pointer to reference it in callbacks.
            connection->user_data = this;
        }

        static void handleEvent(
            mg_connection *connection,
            int event,
            void *data
        ) {
            auto self =
                reinterpret_cast<HTTPRequestProcessorMongoose *>(
                    connection->user_data
                );
            auto request = self->request;
            switch (event)
            {
                case MG_EV_CONNECT:
                    {
                        auto status = *static_cast<int *>(data);
                        if (status != 0)
                        {
                            request->status = HTTPRequest::COMPLETED;
                            auto msg = format::printfString("Failed to connect: '%s'", strerror(status));
                            request->failure(msg);
                            self->inProgress = false;
                        }
                    }
                    break;
                case MG_EV_HTTP_REPLY:
                    {
                        connection->flags |= MG_F_CLOSE_IMMEDIATELY;
                        auto msg = static_cast<http_message *>(data);
                        auto body = std::string(msg->body.p, msg->body.len);
                        request->status = HTTPRequest::COMPLETED;
                        request->success(body);
                        self->inProgress = false;
                    }
                    break;
                case MG_EV_CLOSE:
                    // Only report failure if CLOSE event precedes REPLY one.
                    if (self->inProgress)
                    {
                        request->status = HTTPRequest::COMPLETED;
                        request->failure("Server closed connection");
                    }
                    self->inProgress = false;
                    break;
                default:
                    break;
            }
        }
};
