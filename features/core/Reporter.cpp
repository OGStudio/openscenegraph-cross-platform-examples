FEATURE core.h/Include
#include <functional>
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
            this->callbacks.push_back({callback, name});
        }

        void removeCallback(const std::string &name)
        {
            // This call only deactivates a callback for
            // later removal that happens during next report() call.
            auto callback = this->callbacks.begin();
            for (; callback != this->callbacks.end(); ++callback)
            {
                if (callback->name == name)
                {
                    this->inactiveCallbackNames.push_back(name);
                }
            }
        }

        void report()
        {
            this->removeInactiveCallbacks();

            auto callback = this->callbacks.begin();
            for (; callback != this->callbacks.end(); ++callback)
            {
                callback->callback();
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

    private:
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
