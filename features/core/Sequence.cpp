FEATURE core.h/Include
#include <map>

FEATURE core.h/Impl
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
