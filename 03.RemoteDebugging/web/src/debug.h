
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

// PageDesc Start
#include <string>
#include <vector>

// PageDesc End
// Page Start
#include <functional>

// Page End
// Debugger Start
#include "network.h"
#include <ctime>

// Debugger End

// OSGCPE_DEBUG_DEBUGGER_LOG Start
#include "log.h"
#include "format.h"
#define OSGCPE_DEBUG_DEBUGGER_LOG_PREFIX "osgcpe::debug::Debugger(%p) %s"
#define OSGCPE_DEBUG_DEBUGGER_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_DEBUG_DEBUGGER_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )
// OSGCPE_DEBUG_DEBUGGER_LOG End

namespace osgcpe
{
namespace debug
{

// PageDesc Start
//! Provides serializable representation of a Page instance.
struct PageDesc
{
    std::string title;

    struct Item
    {
        std::string title;
        std::string value;
    };
    std::vector<Item> items;
};
// PageDesc End

// jsonToPageDesc Start
PageDesc jsonToPageDesc(const nlohmann::json &data)
{
    PageDesc desc;

    // Title.
    desc.title = data["title"].get<std::string>();

    // Convert JSON items to DebugPageDesc items.
    auto items = data["items"];
    for (auto item : items)
    {
        auto title = item["title"].get<std::string>();
        auto value = item["value"].get<std::string>();
        desc.items.push_back({ title, value });
    }

    return desc;
}
// jsonToPageDesc End

// Page Start
//! Provides debug page with items to alter.
struct Page
{

    // SETUP.

    std::string title;

    Page(const std::string &title = "") : title(title) { }

    // ITEMS.

    typedef std::function<std::string()> GetterCallback;
    typedef std::function<void(const std::string &)> SetterCallback;

    struct Item
    {
        std::string title;
        GetterCallback getter;
        SetterCallback setter;
    };
    std::vector<Item> items;

    //! Convenience function to add items.
    void addItem(
        const std::string &title,
        GetterCallback getter,
        SetterCallback setter = nullptr
    ) {
        this->items.push_back({title, getter, setter});
    }

// Page End
    // Page+item Start
    Item *item(const std::string &title)
    {
        auto itemCount = this->items.size();
        for (auto i = 0; i < itemCount; ++i)
        {
            Item *item = &this->items[i];
            if (item->title == title)
            {
                return item;
            }
        }
        return 0;
    }
    // Page+item End
    // Page+setDesc Start
    void setDesc(const PageDesc& desc)
    {
        for (auto descItem : desc.items)
        {
            auto item = this->item(descItem.title);
            if (item && item->setter)
            {
                item->setter(descItem.value);
            }
        }
    }
    // Page+setDesc End
// Page Start
};
// Page End

// pageToJSON Start
std::string pageToJSON(Page page)
{
    // Format items.
    std::string format;
    format += "{";
    format += "\"title\":\"%s\",";
    format += "\"value\":\"%s\",";
    format += "\"isWritable\":%d"; // Note the absent comma.
    format += "}";
    std::string itemsJSON = "";
    for (auto item : page.items)
    {
        // Add comma if we're adding second and later items.
        if (!itemsJSON.empty())
        {
            itemsJSON += ",";
        }
        // Add item.
        auto title = item.title;
        auto value = item.getter();
        bool isWritable = (item.setter != nullptr);
        itemsJSON +=
            format::printfString(
                format.c_str(),
                title.c_str(),
                value.c_str(),
                isWritable
            );
    }

    // Format page.
    std::string json;
    json += "{";

    json += "\"title\":\"";
    json += page.title;
    json += "\",";

    json += "\"items\":[";
    json += itemsJSON;
    json += "]"; // Note the absent comma.

    json += "}";
    return json;
}
// pageToJSON End
// debuggerToJSON Start
std::string debuggerToJSON(
    const std::string &debuggerTitle, 
    const std::vector<Page> &pages
) {
    std::string pagesJSON = "";
    for (auto page : pages)
    {
        // Add comma if we're adding the second and following pages.
        if (!pagesJSON.empty())
        {
            pagesJSON += ",";
        }
        pagesJSON += pageToJSON(page);
    }

    // Format debugger.
    std::string json;
    json += "{";

    json += "\"title\":\"";
    json += debuggerTitle;
    json += "\",";

    json += "\"pages\":[";
    json += pagesJSON;
    json += "]"; // Note the absent comma.

    json += "}";

    return json;
}
// debuggerToJSON End

// Debugger Start
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

// Debugger End
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
                //OSGCPE_DEBUG_DEBUGGER_LOG("Process received JSON: '%s'", response.c_str());
                // Only process incoming JSON response if there's response
                if (response.length())
                {
                    this->processJSON(response);
                }
                else
                {
                    OSGCPE_DEBUG_DEBUGGER_LOG("ERROR Received empty response");
                }
                this->isProcessing = false;
            };
            auto failure = [&](std::string reason) {
                OSGCPE_DEBUG_DEBUGGER_LOG(reason.c_str());
                this->isProcessing = false;
            };
            std::string data = debuggerToJSON(this->title, this->pages);
            //OSGCPE_DEBUG_DEBUGGER_LOG("POST JSON: '%s'", data.c_str());
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
// Debugger Start
};
// Debugger End

} // namespace debug
} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_H

