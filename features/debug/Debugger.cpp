FEATURE debug.h/Include
#include <ctime>

FEATURE debug.h/Begin
//! Accumulates and processes DebugPages with the help of network::HTTPClient.
class Debugger
{
    private:
        network::HTTPClient *httpClient;
    public:
        const std::string title;

        Debugger(
            network::HTTPClient *httpClient,
            const std::string &title
        ) :
            httpClient(httpClient),
            title(title)
        { }

    private:
        std::string brokerURL;
    public:
        void setBrokerURL(const std::string &url)
        {
            this->brokerURL = url;
        }

    private:
        std::vector<Page> pages;
    public:
        void addPage(Page page)
        {
            this->pages.push_back(page);
        }

FEATURE debug.h/End
};
