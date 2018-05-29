
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
// Debugger+process-default Start
#include "debug.h"
// TODO REMOVE after testing
#include <ctime>

// Debugger+process-default End
// Debugger+processJSON Start
#include <nlohmann/json.hpp>

// Debugger+processJSON End

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
    public:
        void process()
        {
            // TODO REMOVE after testing
            // 1. Make 5s pause between consequent requests.
            static std::time_t lastProcessDt = 0;
            auto now = std::time(0);
            if (now - lastProcessDt < 5)
            {
                return;
            }
            lastProcessDt = now;
            // TODO Provide non-static flag.
            // 2. Only make new request once previous one has been completed.
            static bool finishedRequest = true;
            if (!finishedRequest)
            {
                return;
            }
            finishedRequest = false;
               
            auto callback = [&](std::string response) {
                // Process incoming JSON response.
                this->processJSON(response);
                finishedRequest = true;
            };
            log::log("process-default");
            std::string data = debug::debuggerToJSON(this->title, this->pages);
            httpClient->post(this->brokerURL, data, callback, callback);
        }
    // Debugger+process-default End
    // Debugger+processJSON Start
    public:
        void processJSON(const std::string &data)
        {
            // TODO Introduce debug page protocol to only deal with internal representation,
            // TODO not explict JSON parsing.
            auto jdata = nlohmann::json::parse(data);
            auto debuggerTitle = jdata["title"].get<std::string>();
            log::logprintf("processJSON. debugger title: '%s'", debuggerTitle.c_str());
            // Ignore different debuggers.
            if (debuggerTitle != this->title)
            {
                // TODO Report different debugger.
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

