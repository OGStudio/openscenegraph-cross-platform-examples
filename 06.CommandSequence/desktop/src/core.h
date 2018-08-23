
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
#include <functional>
#include <string>
#include <vector>

// Reporter End
// Sequence Start
#include <map>

// Sequence End

// OSGCPE_CORE_SEQUENCE_CALLBACK Start
#define OSGCPE_CORE_SEQUENCE_CALLBACK(CALL) [=]() { return CALL; }
// OSGCPE_CORE_SEQUENCE_CALLBACK End
// OSGCPE_CORE_SEQUENCE_LOG Start
#include "log.h"
#include "format.h"
#define OSGCPE_CORE_SEQUENCE_LOG_PREFIX "core::Sequence(%p) %s"
#define OSGCPE_CORE_SEQUENCE_LOG(...) \
    log::logprintf( \
        OSGCPE_CORE_SEQUENCE_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )

// OSGCPE_CORE_SEQUENCE_LOG End

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
            this->callbacks.push_back({callback, name});
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

            // Call one-time callbacks.
            for (auto callback : this->oneTimeCallbacks)
            {
                callback();
            }
            // Remove one-time callbacks.
            this->oneTimeCallbacks.clear();
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
// Sequence Start
class Sequence
{
    public:
        typedef std::vector<std::string> ActionSequence;
        typedef std::function<core::Reporter *()> Callback;

    public:
        Sequence() { }

        std::string name;

        void registerAction(const std::string &name, Callback callback)
        {
            this->actions[name] = callback;
        }

        void setActionSequence(const ActionSequence &sequence)
        {
            // Make sure action sequence is valid.
            if (!this->isActionSequenceValid(sequence))
            {
                OSGCPE_CORE_SEQUENCE_LOG(
                    "ERROR Could not set action sequence because there are "
                    "missing actions in the sequence"
                );
                return;
            }

            this->sequence = sequence;
        }

        void setEnabled(bool state)
        {
            this->isActive = state;

            // Activate.
            if (state)
            {
                this->actionId = -1;
                this->executeNextAction();
            }
        }

    private:
        std::map<std::string, Callback> actions;
        ActionSequence sequence; 
        int actionId = -1;
        bool isActive = false;

        Callback *callback(const std::string &action)
        {
            auto it = this->actions.find(action);
            if (it != this->actions.end())
            {
                return &it->second;
            }
            return 0;
        }

        void executeNextAction()
        {
            // Make sure this sequence is active.
            if (!this->isActive)
            {
                return;
            }

            // Make sure there are actions to execute.
            if (this->actionId + 1 >= this->sequence.size())
            {
                return;
            }

            // Execute action.
            auto action = this->sequence[++this->actionId];
            auto callback = this->callback(action);
            auto reporter = (*callback)();

            // Wait for execution completion report if it exists.
            if (reporter)
            {
                reporter->addOneTimeCallback(
                    [=]{
                        this->executeNextAction();
                    }
                );
            }
            // Otherwise execute the next action right away.
            else
            {
                this->executeNextAction();
            }
        }

        bool isActionSequenceValid(const ActionSequence &actions)
        {
            // Make sure each action has a callback.
            for (auto action : actions)
            {
                if (!this->callback(action))
                {
                    return false;
                }
            }
            return true;
        }
};
// Sequence End

} // namespace core.
} // namespace osgcpe.

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_CORE_H

