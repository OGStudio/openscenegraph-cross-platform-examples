FEATURE core.h/Include
#include <map>

FEATURE core.h/Impl
class Sequence
{
    public:
        typedef std::function<core::Reporter *()> Callback;

        struct Action
        {
            Action(const std::string &name, Callback callback) :
                name(name),
                callback(callback)
            { }

            std::string name;
            Callback callback;
        };

        typedef std::vector<Action> Actions;

    public:
        Sequence() { }

        std::string name;
        bool isRepeatable = false;

        //! Insert new action before the one specified by name.
        void insertAction(Action action, const std::string &name)
        {
            auto it = this->actions.begin();
            for (; it != this->actions.end(); ++it)
            {
                if (it->name == name)
                {
                    this->actions.insert(it, action);
                    return;
                }
            }
        }

        void setActions(Actions actions)
        {
            this->actions = actions;
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
        Actions actions;
        int actionId = -1;
        bool isActive = false;

        void executeNextAction()
        {
            // Make sure this sequence is active.
            if (!this->isActive)
            {
                return;
            }

            // Make sure there are actions to execute.
            if (this->actionId + 1 >= this->actions.size())
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
            auto action = this->actions[++this->actionId];
            auto reporter = action.callback();

            //CORE_SEQUENCE_LOG("Executed action '%s'", action.c_str());

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
};
