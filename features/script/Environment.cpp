FEATURE script.h/Impl
//! Serve as a hub for scriptable entities.
class Environment
{
    public:
        Environment() { }

        void addClient(
            EnvironmentClient *client,
            const std::vector<std::string> &keys
        ) {
            // Map keys to the client.
            for (auto key : keys)
            {
                this->keys[key] = client;
            }
        }

        //! Execute a call by finding suitable client to delegate the call to.
        std::vector<std::string> call(
            const std::string &key,
            const std::vector<std::string> &values
        ) {
            if (this->isVerbose)
            {
                SCRIPT_ENVIRONMENT_LOG(
                    "call(%s, {%s})",
                    key.c_str(),
                    format::stringsToString(values).c_str()
                );
            }

            // Make sure there is a client that responds to the key.
            auto it = this->keys.find(key);
            if (it == this->keys.end())
            {
                SCRIPT_ENVIRONMENT_LOG(
                    "ERROR Could not find a client that responds to '%s' key",
                    key.c_str()
                );
                return { };
            }

            // Make sure the client has callback assigned.
            auto client = it->second;
            if (!client->call)
            {
                SCRIPT_ENVIRONMENT_LOG(
                    "ERROR Could not process '%s' key because the client "
                    "does not have a callback assigned",
                    key.c_str()
                );
                return { };
            }

            // Perform the call.
            return client->call(key, values);
        }

        //! Verbose Environment logs all calls.
        void setVerbose(bool state)
        {
            this->isVerbose = state;
        }

    private:
        std::map<std::string, EnvironmentClient *> keys;
        bool isVerbose = false;
};
