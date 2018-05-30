
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
// Debugger+process-web Start
#include "debug.h"

// Debugger+process-web End


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

    // Debugger+process-web Start
    public:
        void process()
        {
            // Only run once to debug first.
            static bool runOnce = true;
            if (!runOnce)
            {
                return;
            }
            runOnce = false;
            OSGCPE_DEBUGGER_LOG("process-web");
    
            std::string pagesJSON = "";
    
            auto page = this->pages.begin();
            for (; page != this->pages.end(); ++page)
            {
                // Add comma if we're adding the second and following pages.
                if (!pagesJSON.empty())
                {
                    pagesJSON += ",";
                }
                pagesJSON += debug::pageToJSON(*page);
            }
    
            // Format pages.
            std::string json;
            json += "{";
    
            json += "\"title\":\"";
            json += this->title;
            json += "\",";
    
            json += "\"pages\":[";
            json += pagesJSON;
            json += "]"; // Note the absent comma.
    
            json += "}";
    
            OSGCPE_DEBUGGER_LOG("All pages");
            OSGCPE_DEBUGGER_LOG(json.c_str());
            // TODO send JSON.
        }
        // TODO send JSON?
        // TODO receive JSON?
    // Debugger+process-web End

};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUGGER_H

