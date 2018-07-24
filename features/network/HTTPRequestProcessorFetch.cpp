FEATURE network.h/Include
#include "format.h"

FEATURE network.h/TypeDef
typedef HTTPRequestProcessorFetch HTTPRequestProcessor;

FEATURE network.h/Impl
//! Internal class to process HTTP GET/POST requests with FetchAPI.
class HTTPRequestProcessorFetch
{
    public:
        HTTPRequestProcessorFetch(HTTPRequest *request) :
            request(request),
            inProgress(false)
        {
            emscripten_fetch_attr_init(&this->client);
            this->client.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
            // Save 'this' pointer to reference it in callbacks.
            this->client.userData = this;
            // Start.
            this->processRequest();
        }

        ~HTTPRequestProcessorFetch()
        {
            this->client.userData = 0;
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

            // Set request method.
            std::string method = "GET";
            if (data)
            {
                method = "POST";
            }
            strcpy(this->client.requestMethod, method.c_str());

            // Set body.
            if (data)
            {
                /*
                // Set headers.
                const char *headers[] = {
                    "Content-Type", "text/plain; charset=utf-8",
                    0
                };
                this->client.requestHeaders = headers;
                */
                this->client.requestData = data;
                this->client.requestDataSize = strlen(data);
            }

            // Set callbacks.
            this->client.onsuccess = handleSuccess;
            this->client.onerror = handleFailure;

            // Perform request.
            emscripten_fetch(&this->client, url);
        }

        static void handleSuccess(emscripten_fetch_t *fetch)
        {
            auto self =
                reinterpret_cast<HTTPRequestProcessorFetch *>(fetch->userData);
            if (self)
            {
                self->inProgress = false;
                std::string body(fetch->data, fetch->numBytes);
                // Report success.
                auto request = self->request;
                request->status = HTTPRequest::COMPLETED;
                request->success(body);
            }
            // Free data associated with this request.
            emscripten_fetch_close(fetch);
        }

        static void handleFailure(emscripten_fetch_t *fetch)
        {
            auto self =
                reinterpret_cast<HTTPRequestProcessorFetch *>(fetch->userData);
            if (self)
            {
                self->inProgress = false;
                auto msg = format::printfString("Failed. Status code: '%d'", fetch->status);
                // Report failure.
                auto request = self->request;
                request->status = HTTPRequest::COMPLETED;
                request->failure(msg);
            }
            // Free data associated with this request.
            emscripten_fetch_close(fetch);
        }
};
