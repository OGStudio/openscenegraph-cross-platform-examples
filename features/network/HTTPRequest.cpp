FEATURE network.h/Include
#include <functional>
#include <string>

FEATURE network.h/Impl
//! HTTP request container
class HTTPRequest
{
    public:
        typedef std::function<void(std::string)> Callback;

        enum STATUS
        {
            NONE,
            IN_PROGRESS,
            COMPLETED
        };

        // If data is emtpy, GET request is issued.
        // Otherwise POST request is issued.
        HTTPRequest(
            const std::string &url,
            const std::string &data,
            Callback success,
            Callback failure
        ) :
            url(url),
            data(data),
            success(success),
            failure(failure),
            status(NONE)
        { }

        const std::string url;
        const std::string data;
        Callback success,
        Callback failure
        STATUS status;
};
