
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUGGER_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUGGER_H

#include "DebugPage.h"
#include "HTTPClient.h"
// Debugger+process-default Start
#include "debug.h"
#include <ctime>

// Debugger+process-default End
// Debugger+processJSON Start
#include <nlohmann/json.hpp>

// Debugger+processJSON End

// Debugger+OSGCPE_DEBUGGER_LOG Start
#include "log.h"
#include "format.h"
#define OSGCPE_DEBUGGER_LOG_PREFIX "osgcpe-Debugger(%p) %s"
#define OSGCPE_DEBUGGER_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_DEBUGGER_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )

// Debugger+OSGCPE_DEBUGGER_LOG End

namespace osgcpe
{

class Debugger
{
    private:
        HTTPClient *httpClient;
    public:
        const std::string title;

        Debugger(
            HTTPClient *httpClient,
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
        std::vector<DebugPage> pages;
    public:
        void addDebugPage(DebugPage page)
        {
            this->pages.push_back(page);
        }
    // Debugger+page Start
    public:
        DebugPage *page(const std::string &title)
        {
            auto pageCount = this->pages.size();
            for (auto i = 0; i < pageCount; ++i)
            {
                DebugPage *page = &this->pages[i];
                if (page->title == title)
                {
                    return page;
                }
            }
            return 0;
        }
    // Debugger+page End

    // Debugger+process-default Start
    private:
        // Request frequency control.
        std::time_t lastProcessDt = 0;
        const int processPause = 1; // In seconds.
        // Request sequencing.
        bool isProcessing = false;
    public:
        void process()
        {
            // 1. Make sure `processPause` number of seconds passed since last `process()` execution.
            auto now = std::time(0);
            if (now - this->lastProcessDt < this->processPause)
            {
                return;
            }
            this->lastProcessDt = now;
    
            // 2. Only make new request once previous one has been completed.
            if (this->isProcessing)
            {
                return;
            }
            this->isProcessing = true;
               
            auto success = [&](std::string response) {
                // Process incoming JSON response.
                this->processJSON(response);
                this->isProcessing = false;
            };
            auto failure = [&](std::string reason) {
                OSGCPE_DEBUGGER_LOG(reason.c_str());
                this->isProcessing = false;
            };
            std::string data = debug::debuggerToJSON(this->title, this->pages);
            httpClient->post(this->brokerURL, data, success, failure);
        }
    // Debugger+process-default End
    // Debugger+processJSON Start
    public:
        void processJSON(const std::string &data)
        {
            // TODO Work with DebugPageDesc here instead of raw JSON?
            auto jdata = nlohmann::json::parse(data);
            auto debuggerTitle = jdata["title"].get<std::string>();
            // Ignore different debuggers.
            if (debuggerTitle != this->title)
            {
                OSGCPE_DEBUGGER_LOG("WARNING Ignoring debugger with different title");
                return;
            }
            auto jpages = jdata["pages"];
            for (auto jpage : jpages)
            {
                auto pageDesc = debug::jsonToPageDesc(jpage);
                auto page = this->page(pageDesc.title);
                if (page)
                {
                    page->setDesc(pageDesc);
                }
            }
        }
    // Debugger+processJSON End

};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUGGER_H

