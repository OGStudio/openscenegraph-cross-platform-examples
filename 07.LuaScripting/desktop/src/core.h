
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_CORE_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_CORE_H

// Reporter Start
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

// Reporter End



namespace osgcpe
{
namespace core
{

// Reporter Start
class Reporter
{
    public:
        typedef std::function<void()> Callback;

    public:
        Reporter() { }

        std::string name;

        void addCallback(Callback callback, const std::string &name = "")
        {
            // Work around callback reactivation happenning
            // before `report()` call.
            if (this->reactivateInactiveCallback(name))
            {
                //CORE_REPORTER_LOG("reactivated callback named '%s'", name.c_str());
                return;
            }

            this->callbacks.push_back({callback, name});
            //CORE_REPORTER_LOG("added callback named '%s'", name.c_str());
        }

        void addOneTimeCallback(Callback callback)
        {
            this->oneTimeCallbacks.push_back(callback);
        }

        void removeCallback(const std::string &name)
        {
            // This call only deactivates a callback for
            // later removal that happens during next report() call.
            for (auto callback : this->callbacks)
            {
                if (callback.name == name)
                {
                    this->inactiveCallbackNames.push_back(name);
                }
            }
        }

        void report()
        {
            this->removeInactiveCallbacks();

            // Call normal callbacks.
            for (auto callback : this->callbacks)
            {
                callback.callback();
            }

            // Iterate over duplicated one-time callbacks.
            auto oneTimeCallbacks = this->oneTimeCallbacks; 
            // Remove one-time callbacks.
            this->oneTimeCallbacks.clear();
            
            // Call one-time callbacks.
            for (auto callback : oneTimeCallbacks)
            {
                callback();
            }
        }

    private:
        struct NamedCallback
        {
            Callback callback;
            std::string name;
        };

        std::vector<NamedCallback> callbacks;
        std::vector<std::string> inactiveCallbackNames;
        std::vector<Callback> oneTimeCallbacks;

    private:
        bool reactivateInactiveCallback(const std::string &name)
        {
            auto inactives = &this->inactiveCallbackNames;
            auto it = std::find(inactives->begin(), inactives->end(), name);
            if (it != inactives->end())
            {
                inactives->erase(it);
                return true;
            }
            return false;
        }

        void removeInactiveCallbacks()
        {
            // Loop through the names of inactive callbacks.
            auto name = this->inactiveCallbackNames.begin();
            for (; name != this->inactiveCallbackNames.end(); ++name)
            {
                // Loop through callbacks to find matching name.
                auto callback = this->callbacks.begin();
                for (; callback != this->callbacks.end(); ++callback)
                {
                    if (callback->name == *name)
                    {
                        // Remove matching callback.
                        this->callbacks.erase(callback);
                        break;
                    }
                }
            }
            // Clear the list of inactive callbacks.
            this->inactiveCallbackNames.clear();
        }
};
// Reporter End

} // namespace core.
} // namespace osgcpe.

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_CORE_H

