
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_H

#include "debug-extlib.h"



namespace osgcpe
{
namespace debug
{



    // Debugger+page Start
    public:
        Page *page(const std::string &title)
        {
            auto pageCount = this->pages.size();
            for (auto i = 0; i < pageCount; ++i)
            {
                Page *page = &this->pages[i];
                if (page->title == title)
                {
                    return page;
                }
            }
            return 0;
        }
    // Debugger+page End
    // Debugger+process Start
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
                //OSGCPE_DEBUG_DEBUGGER_LOG("Process JSON: '%s'", response.c_str());
                // Process incoming JSON response.
                this->processJSON(response);
                this->isProcessing = false;
            };
            auto failure = [&](std::string reason) {
                OSGCPE_DEBUG_DEBUGGER_LOG(reason.c_str());
                this->isProcessing = false;
            };
            std::string data = debuggerToJSON(this->title, this->pages);
            this->httpClient->post(this->brokerURL, data, success, failure);
        }
    // Debugger+process End
    // Debugger+processJSON Start
    public:
        void processJSON(const std::string &data)
        {
            // TODO Work with PageDesc here instead of raw JSON?
            auto jdata = nlohmann::json::parse(data);
            auto debuggerTitle = jdata["title"].get<std::string>();
            // Ignore different debuggers.
            if (debuggerTitle != this->title)
            {
                OSGCPE_DEBUG_DEBUGGER_LOG("WARNING Ignoring debugger with different title");
                return;
            }
            auto jpages = jdata["pages"];
            for (auto jpage : jpages)
            {
                auto pageDesc = jsonToPageDesc(jpage);
                auto page = this->page(pageDesc.title);
                if (page)
                {
                    page->setDesc(pageDesc);
                }
            }
        }
    // Debugger+processJSON End


} // namespace debug
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_H

