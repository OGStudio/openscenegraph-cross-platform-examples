FEATURE core.h/Include
#include <map>

FEATURE core.h/Impl
class Sequence
{
    public:
        typedef std::vector<std::string> Actions;
        typedef std::function<core::Reporter *()> Callback;

    public:
        Sequence() { }

        std::string name;
        bool isRepeatable = true;

        void registerAction(const std::string &name, Callback callback)
        {
            this->actions[name] = callback;
        }

        void setActions(const Actions &sequence)
        {
            this->sequence = sequence;
        }

        void setEnabled(bool state)
        {
            // Make sure action sequence is valid.
            if (!this->isActionSequenceValid(this->sequence))
            {
                OSGCPE_CORE_SEQUENCE_LOG(
                    "ERROR Could not set action sequence because there are "
                    "missing actions in the sequence"
                );
                return;
            }

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
        Actions sequence; 
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
                // Quit if this sequence is not repeatable.
                if (!this->isRepeatable)
                {
                    return;
                }
                // Reset otherwise.
                this->actionId = -1;
            }

            // Execute action.
            auto action = this->sequence[++this->actionId];
            auto callback = this->callback(action);
            auto reporter = (*callback)();

            //OSGCPE_CORE_SEQUENCE_LOG("Executed action '%s'", action.c_str());

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

        bool isActionSequenceValid(const Actions &actions)
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
