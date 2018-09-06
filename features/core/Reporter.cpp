FEATURE core.h/Include
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

FEATURE core.h/Impl
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
